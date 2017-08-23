// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"
#include "AISimplexAppraisalModule.h"
#include "Emotion/AIEmotionKnowledge.h"

UAISimplexEmotionEngine::UAISimplexEmotionEngine()
{
}

void UAISimplexEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;

	DecayFactor = Personality.GetDecayFactor();

	Memory = NewObject<UAIEmotionKnowledge>();

	AppraisalModule = NewObject<UAISimplexAppraisalModule>();
	AppraisalModule->InitializeAppraisalModule(EmotionKnowledge, Memory, &Personality);
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
			CurrentEmotionalState += (*Iterator);
		}
	}
}

float UAISimplexEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAISimplexEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	bool bIsImpulsePositive = value > 0.0f;
	if(bIsImpulsePositive)
	{
		CurrentEmotionalState += FSimplexPADPoint::Joy * Personality.GetInfluenceOnEmotion(true) * FMath::Abs(value);
	}
	else
	{
		CurrentEmotionalState += FSimplexPADPoint::Distress * Personality.GetInfluenceOnEmotion(false) * FMath::Abs(value);
	}
}

//Temporary, just for the backward compability with "old" SandboxAI emotion engines implementation
void UAISimplexEmotionEngine::UpdateRunAction(float JoyDistress)
{
	float Value = 0.5f * (-JoyDistress + 1.0f);

	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], Value));
}