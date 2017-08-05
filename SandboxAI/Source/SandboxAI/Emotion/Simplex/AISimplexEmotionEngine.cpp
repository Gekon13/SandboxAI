// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"

UAISimplexEmotionEngine::UAISimplexEmotionEngine()
{
	SomeName = TEXT("Simplex");
	SomeOtherName = TEXT("Simplex");
}

void UAISimplexEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;

	DecayFactor = Personality.GetDecayFactor();
}

void UAISimplexEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);

	CurrentEmotionalState = FSimplexPADPoint::InterpTo(CurrentEmotionalState, NeutralEmotionalState, DeltaSeconds, DecayFactor);

	float DistanceFromJoy = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Joy);
	float DistanceFromDistress = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Distress);
	float JoyDistress = FMath::Clamp(DistanceFromDistress - DistanceFromJoy, -1.0f, 1.0f);

	//Temporary, will be removed later
	UpdateRunAction(JoyDistress);
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