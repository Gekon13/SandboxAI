// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"
#include "AISimplexAppraisalModule.h"
#include "Emotion/AIEmotionKnowledge.h"

UAISimplexEmotionEngine::UAISimplexEmotionEngine() : Super()
{
	Memory = CreateDefaultSubobject<UAIEmotionKnowledge>(TEXT("Emotion memory"));

	AppraisalModule = CreateDefaultSubobject<UAISimplexAppraisalModule>("OCC appraisal module");
}

void UAISimplexEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* InEmotionKnowledge)
{
	Super::InitializeEmotionEngine(InEmotionKnowledge);

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;

	DecayFactor = Personality.GetDecayFactor();

	if(AppraisalModule)
	{
		AppraisalModule->InitializeAppraisalModule(EmotionKnowledge, Memory, &Personality);
	}
}

void UAISimplexEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);

	CurrentEmotionalState = FSimplexPADPoint::InterpTo(CurrentEmotionalState, NeutralEmotionalState, DeltaSeconds, DecayFactor);

	float DistanceFromJoy = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Joy);
	float DistanceFromDistress = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Distress);
	float JoyDistress = FMath::Clamp(DistanceFromDistress - DistanceFromJoy, -1.0f, 1.0f);

	//Temporary, will be removed later (when real knowledge about actions->consequences will come)
	UpdateRunAction(JoyDistress);
}

void UAISimplexEmotionEngine::HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	if(AppraisalModule)
	{
		TArray<FSimplexPADPoint> EmotionalStateChanges = AppraisalModule->DoAppraisal(EmotionActionName, SourceActor, TargetActor);

		for(auto Iterator = EmotionalStateChanges.CreateIterator(); Iterator; ++Iterator)
		{
			UE_LOG(LogTemp, Warning, TEXT("GeneratedEmotion: %s"), *((*Iterator).ToString()));
			CurrentEmotionalState += (*Iterator);
		}
	}
}

float UAISimplexEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAISimplexEmotionEngine::DirectValencedImpulseInternal(float Value, bool bContinuous)
{
	bool bIsImpulsePositive = Value > 0.0f;
	if(bIsImpulsePositive)
	{
		CurrentEmotionalState += FSimplexPADPoint::Joy * Personality.GetInfluenceOnEmotion(true) * FMath::Abs(Value);
	}
	else
	{
		CurrentEmotionalState += FSimplexPADPoint::Distress * Personality.GetInfluenceOnEmotion(false) * FMath::Abs(Value);
	}
}

//Temporary, just for the backward compability with "old" SandboxAI emotion engines implementation
void UAISimplexEmotionEngine::UpdateRunAction(float JoyDistress)
{
	float Value = 0.5f * (-JoyDistress + 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("JoyDistress: %.3f"), JoyDistress);

	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], Value));
}