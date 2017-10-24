// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEmotionPointPAD.generated.h"

/**
 * Common PAD point structure for emotion classes
 */
USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionPointPAD : public FVector
{
	GENERATED_BODY()

public:
	static float AIEmotionPointPADSpaceRadius;

	FORCEINLINE FAIEmotionPointPAD();
	FORCEINLINE FAIEmotionPointPAD(const FVector& source);
	FORCEINLINE FAIEmotionPointPAD(const float& Pleasure, const float& Arousal, const float& Dominance);
};

FAIEmotionPointPAD::FAIEmotionPointPAD() : Super(FVector::ZeroVector) {}
FAIEmotionPointPAD::FAIEmotionPointPAD(const FVector& source) : Super(source) {}
FAIEmotionPointPAD::FAIEmotionPointPAD(const float& Pleasure, const float& Arousal, const float& Dominance) : Super(Pleasure, Arousal, Dominance) {}
