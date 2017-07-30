// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"

UAISimplexEmotionEngine::UAISimplexEmotionEngine()
{
	SomeName = TEXT("Simplex");
	SomeOtherName = TEXT("Simplex");
}

void UAISimplexEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge)
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

	if(JoyDistress < 0.0f)
	{
		MakeDecision(FEmotionDecisionInfo("Faster", FMath::Abs(JoyDistress), EEmotionPrimary::Distress));
	}
	else if(JoyDistress > 0.0f)
	{
		MakeDecision(FEmotionDecisionInfo("Slower", JoyDistress, EEmotionPrimary::Joy));
	}
}

float UAISimplexEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAISimplexEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	if(value < 0.0f)
	{
		CurrentEmotionalState += FSimplexPADPoint::Distress * Personality.GetInfluenceOnEmotion(false) * FMath::Abs(value);
	}
	else if(value > 0.0f)
	{
		CurrentEmotionalState += FSimplexPADPoint::Joy * Personality.GetInfluenceOnEmotion(true) * FMath::Abs(value);
	}
}