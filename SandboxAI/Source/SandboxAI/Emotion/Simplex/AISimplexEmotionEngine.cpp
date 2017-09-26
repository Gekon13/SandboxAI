// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"
#include "AISimplexAppraisalModule.h"
#include "../Common/AIEmotionKnowledge.h"

#define AddEmotionToFAIEmotionState(EmotionState, EmotionName, CurrentPADState) EmotionState.Add(FAISingleEmotionState(EEmotionName::EmotionName, FSimplexPADPoint::CalculateEmotionStrength(CurrentPADState, FSimplexPADPoint::EmotionName), true));

UAISimplexEmotionEngine::UAISimplexEmotionEngine()
{
	Memory = CreateDefaultSubobject<UAIEmotionKnowledge>(TEXT("Emotion memory"));

	AppraisalModule = CreateDefaultSubobject<UAISimplexAppraisalModule>("OCC appraisal module");
}

FAIEmotionState UAISimplexEmotionEngine::GetEmotionState() const
{
	FAIEmotionState CurrentEmotionState;

	AddEmotionToFAIEmotionState(CurrentEmotionState, Joy, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Distress, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Hope, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Fear, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Love, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Hate, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Happyfor, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Pitty, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Admiration, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Gloating, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Pride, CurrentEmotionalState);
	AddEmotionToFAIEmotionState(CurrentEmotionState, Shame, CurrentEmotionalState);

	return CurrentEmotionState;
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

	//Temporary, will be removed later (when real knowledge about actions->consequences will come)
	UpdateRunAction();
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
void UAISimplexEmotionEngine::UpdateRunAction()
{
	float Value = FSimplexPADPoint::Dist(CurrentEmotionalState, NeutralEmotionalState);
	
	if(FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint(1, 1, 1)) > FSimplexPADPoint::Dist(NeutralEmotionalState, FSimplexPADPoint(1, 1, 1)))
	{
		Value *= -1.0f;
	}
	Value = 1.0f - (Value + 1.0f) * 0.5f;

	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], FMath::Clamp(Value, 0.0f, 1.0f)));
}