// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexStructures.h"

FSimplexPADPoint FSimplexPADPoint::Joy = FSimplexPADPoint(0.4f, 0.2f, 0.1f);
FSimplexPADPoint FSimplexPADPoint::Distress = FSimplexPADPoint(-0.4f, -0.2f, -0.5f);

float FSimplexPADPoint::Dist(const FSimplexPADPoint& From, const FSimplexPADPoint& To)
{
	return FMath::Sqrt(FMath::Square(From.Pleasure - To.Pleasure) + FMath::Square(From.Arousal - To.Arousal) + FMath::Square(From.Dominance - To.Dominance));
}

FSimplexPADPoint FSimplexPADPoint::InterpTo(const FSimplexPADPoint& Current, const FSimplexPADPoint& Target, float DeltaTime, float InterpSpeed)
{
	if(InterpSpeed <= 0.0f)
	{
		return Target;
	}

	// Difference between colors
	const float Dist = FSimplexPADPoint::Dist(Target, Current);

	// If distance is too small, just set the desired color
	if(Dist < KINDA_SMALL_NUMBER)
	{
		return Target;
	}

	// Delta change, Clamp so we do not over shoot.
	const FSimplexPADPoint DeltaMove = (Target - Current) * FMath::Clamp<float>(DeltaTime * InterpSpeed, 0.0f, 1.0f);

	return Current + DeltaMove;
}
