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
		EEmotionName Emotion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActive;

public:
	FORCEINLINE FAISingleEmotionState();
	FORCEINLINE FAISingleEmotionState(EEmotionName emotion);
	FORCEINLINE FAISingleEmotionState(EEmotionName emotion, float strength);
	FORCEINLINE FAISingleEmotionState(EEmotionName emotion, bool active);
	FORCEINLINE FAISingleEmotionState(EEmotionName emotion, float strength, bool active); // prefered constructor

	FORCEINLINE FString ToString() const;
};

FAISingleEmotionState::FAISingleEmotionState() : Emotion(EEmotionName::None), Strength(0.0f), bActive(false) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionName emotion) : Emotion(emotion), Strength(0.0f), bActive(false) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionName emotion, float strength) : Emotion(emotion), Strength(strength), bActive(strength > 0.0f) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionName emotion, bool active) : Emotion(emotion), Strength(0.0f), bActive(active) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionName emotion, float strength, bool active) : Emotion(emotion), Strength(strength), bActive(active) {}

FString FAISingleEmotionState::ToString() const { return FString::Printf(TEXT("Name %s, IsActive: %s, Strength: %.4f"), *FAIEmotionConstants::EmotionNames[Emotion], bActive ? TEXT("true") : TEXT("false"), Strength); }

USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAISingleEmotionState> Emotions;

public:
	FORCEINLINE FAIEmotionState();
	FORCEINLINE FAIEmotionState(const FAISingleEmotionState& emotion);
	FORCEINLINE FAIEmotionState(const TArray<FAISingleEmotionState>& emotions);

	FORCEINLINE const FAISingleEmotionState& operator[] (int32 index) const { return Emotions[index]; }
	FORCEINLINE FAISingleEmotionState& operator[]  (int32 index) { return Emotions[index]; }
	FORCEINLINE int32 Num() const { return Emotions.Num(); }
	FORCEINLINE void Add(const FAISingleEmotionState& emotion) { Emotions.Add(emotion); }
	FORCEINLINE void Add(const TArray<FAISingleEmotionState>& emotions) { Emotions.Append(emotions); }

	FString ToString();
};

FAIEmotionState::FAIEmotionState() {}
FAIEmotionState::FAIEmotionState(const FAISingleEmotionState& emotion) { Emotions.Add(emotion); }
FAIEmotionState::FAIEmotionState(const TArray<FAISingleEmotionState>& emotions) {	Emotions.Append(emotions); }