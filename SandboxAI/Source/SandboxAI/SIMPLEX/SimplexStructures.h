// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimplexStructures.generated.h"

//Representation of a point in PAD space
//All values are in range from -1 to 1
USTRUCT(BlueprintType)
struct SANDBOXAI_API FSimplexPADPoint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Pleasure;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Arousal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Dominance;

	static FSimplexPADPoint Joy;
	static FSimplexPADPoint Distress;

public:
	FORCEINLINE FSimplexPADPoint(float InPleasure = 0.0f, float InArousal = 0.0f, float InDominance = 0.0f) : Pleasure(FMath::Clamp(InPleasure, -1.0f, 1.0f)), Arousal(FMath::Clamp(InArousal, -1.0f, 1.0f)), Dominance(FMath::Clamp(InDominance, -1.0f, 1.0f)) { }

	FORCEINLINE FSimplexPADPoint operator+(const FSimplexPADPoint& PointB) const
	{
		return FSimplexPADPoint(Pleasure + PointB.Pleasure, Arousal + PointB.Arousal, Dominance + PointB.Dominance);
	}

	FORCEINLINE FSimplexPADPoint& operator+=(const FSimplexPADPoint& PointB)
	{
		Pleasure = FMath::Clamp(Pleasure + PointB.Pleasure, -1.0f, 1.0f);
		Arousal = FMath::Clamp(Arousal + PointB.Arousal, -1.0f, 1.0f);
		Dominance = FMath::Clamp(Dominance + PointB.Dominance, -1.0f, 1.0f);
		
		return *this;
	}

	FORCEINLINE FSimplexPADPoint operator-(const FSimplexPADPoint& PointB) const
	{
		return FSimplexPADPoint(Pleasure - PointB.Pleasure, Arousal - PointB.Arousal, Dominance - PointB.Dominance);
	}

	FORCEINLINE FSimplexPADPoint& operator-=(const FSimplexPADPoint& PointB)
	{
		Pleasure = FMath::Clamp(Pleasure - PointB.Pleasure, -1.0f, 1.0f);
		Arousal = FMath::Clamp(Arousal - PointB.Arousal, -1.0f, 1.0f);
		Dominance = FMath::Clamp(Dominance - PointB.Dominance, -1.0f, 1.0f);
		
		return *this;
	}

	FORCEINLINE FSimplexPADPoint operator*(float Scalar) const
	{
		return FSimplexPADPoint(Scalar * Pleasure, Scalar * Arousal, Scalar * Dominance);
	}

	FORCEINLINE FSimplexPADPoint& operator*=(float Scalar)
	{
		Pleasure = FMath::Clamp(Pleasure * Scalar, -1.0f, 1.0f);
		Arousal = FMath::Clamp(Arousal * Scalar, -1.0f, 1.0f);
		Dominance = FMath::Clamp(Dominance * Scalar, -1.0f, 1.0f);

		return *this;
	}

	FORCEINLINE FSimplexPADPoint operator/(float Scalar) const
	{
		return FSimplexPADPoint(Pleasure / Scalar, Arousal / Scalar, Dominance / Scalar);
	}

	FORCEINLINE FSimplexPADPoint& operator/=(float Scalar)
	{
		Pleasure = FMath::Clamp(Pleasure / Scalar, -1.0f, 1.0f);
		Arousal = FMath::Clamp(Arousal / Scalar, -1.0f, 1.0f);
		Dominance = FMath::Clamp(Dominance / Scalar, -1.0f, 1.0f);

		return *this;
	}

	FORCEINLINE FSimplexPADPoint& operator=(const FSimplexPADPoint& PointB)
	{
		Pleasure = PointB.Pleasure;
		Arousal = PointB.Arousal;
		Dominance = PointB.Dominance;

		return *this;
	}

	FORCEINLINE bool operator==(const FSimplexPADPoint& PointB) const
	{
		return FMath::IsNearlyEqual(Pleasure, PointB.Pleasure) && FMath::IsNearlyEqual(Arousal, PointB.Arousal) && FMath::IsNearlyEqual(Dominance, PointB.Dominance);
	}

	FORCEINLINE bool operator!=(const FSimplexPADPoint& PointB) const
	{
		return !FMath::IsNearlyEqual(Pleasure, PointB.Pleasure) || !FMath::IsNearlyEqual(Arousal, PointB.Arousal) || !FMath::IsNearlyEqual(Dominance, PointB.Dominance);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("(Pleasure = %.5f, Arousal = %.5f, Dominance = %.5f)"), Pleasure, Arousal, Dominance);
	}

	static float Dist(const FSimplexPADPoint& From, const FSimplexPADPoint& To);
	static FSimplexPADPoint InterpTo(const FSimplexPADPoint& Current, const FSimplexPADPoint& Target, float DeltaTime, float InterpSpeed);
};

FORCEINLINE FSimplexPADPoint operator*(float scalar, const FSimplexPADPoint& PADPoint)
{
	return FSimplexPADPoint(scalar * PADPoint.Pleasure, scalar * PADPoint.Arousal, scalar * PADPoint.Dominance);
}

//Representation of Big Five personality traits (Five Factor Model, OCEAN)
//All values are in range from -1 to 1
USTRUCT(BlueprintType)
struct SANDBOXAI_API FSimplexPersonality
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float OpenessToExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Conscientiousness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Extroversion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Agreeableness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Neuroticism;

public:
	FORCEINLINE FSimplexPADPoint ToPADPoint() const
	{
		//Mehrabian’s Big Five to PAD transformation rules
		return FSimplexPADPoint(
			0.21f * Extroversion + 0.59f * Agreeableness + 0.19f * Neuroticism,
			0.15f * OpenessToExperience + 0.3f * Agreeableness + 0.57 * Neuroticism,
			0.25f * OpenessToExperience + 0.17f * Conscientiousness + 0.6f * Extroversion - 0.32f * Agreeableness
		);
	}
};