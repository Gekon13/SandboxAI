// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEmotionConstants.h"
#include "AIEmotionState.generated.h"


USTRUCT(BlueprintType)
struct PROJECT_API FAISingleEmotionState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionPrimary Emotion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActive;

public:
	FAISingleEmotionState();
	FAISingleEmotionState(EEmotionPrimary emotion);
	FAISingleEmotionState(EEmotionPrimary emotion, float strength);
	FAISingleEmotionState(EEmotionPrimary emotion, bool active);
	FAISingleEmotionState(EEmotionPrimary emotion, float strength, bool active);
};

USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAISingleEmotionState> Emotions;

public:
	FAIEmotionState();
	FAIEmotionState(const FAISingleEmotionState& emotion);
	FAIEmotionState(const TArray<FAISingleEmotionState>& emotions);

	FORCEINLINE const FAISingleEmotionState& operator[] (int32 index) const { return Emotions[index]; }
	FORCEINLINE FAISingleEmotionState& operator[]  (int32 index) { return Emotions[index]; }
	FORCEINLINE int32 Num() const { return Emotions.Num(); }
	FORCEINLINE void Add(const FAISingleEmotionState& emotion) { Emotions.Add(emotion); }
	FORCEINLINE void Add(const TArray<FAISingleEmotionState>& emotions) { Emotions.Append(emotions); }
};

