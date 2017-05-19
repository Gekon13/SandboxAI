// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "ExampleSplineAIController.h"

AExampleSplineAIController::AExampleSplineAIController()
{
	EmotionValence = 0.0f;
	EmotionValenceMin = -100.0f;
	EmotionValenceMax = 100.0f;
	EmotionValenceNullifyRate = 25.0f;

	EmotionColorMin = FLinearColor::Red;
	EmotionColorMax = FLinearColor::Green;
}

void AExampleSplineAIController::BeginPlay()
{
	Super::BeginPlay();

	EmotionValence = 0.0f;
	UpdateActorEmotionalStateConsequences();
}

void AExampleSplineAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float value = FMath::Abs(EmotionValence);
	float sign = FMath::Sign(EmotionValence);

	value = FMath::Max(0.0f, value - EmotionValenceNullifyRate * DeltaSeconds);
	EmotionValence = value * sign;
}

void AExampleSplineAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement)
{
	switch (emotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		EmotionValence += emotionStimulusElement.Power;
		break;
	case EEmotionStimulusElementType::ENegative:
		EmotionValence -= emotionStimulusElement.Power;
		break;
	}
	EmotionValence = FMath::Clamp<float>(EmotionValence, EmotionValenceMin, EmotionValenceMax);

	UpdateActorEmotionalStateConsequences();
}

void AExampleSplineAIController::UpdateActorEmotionalStateConsequences()
{
	float value = (EmotionValence - EmotionValenceMin) / (EmotionValenceMax - EmotionValenceMin);

	SetFollowSpeedCoefficient(1.0f - value);

	FLinearColor color = FMath::Lerp<FLinearColor>(EmotionColorMin, EmotionColorMax, value);
	SetEmotionVisualColor(color);
}