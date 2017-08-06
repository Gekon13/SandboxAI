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
	FORCEINLINE FAISingleEmotionState();
	FORCEINLINE FAISingleEmotionState(EEmotionPrimary emotion);
	FORCEINLINE FAISingleEmotionState(EEmotionPrimary emotion, float strength);
	FORCEINLINE FAISingleEmotionState(EEmotionPrimary emotion, bool active);
	FORCEINLINE FAISingleEmotionState(EEmotionPrimary emotion, float strength, bool active);
};

FAISingleEmotionState::FAISingleEmotionState() : Emotion(EEmotionPrimary::None), Strength(0.0f), bActive(false) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion) : Emotion(emotion), Strength(0.0f), bActive(false) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, float strength) : Emotion(emotion), Strength(strength), bActive(false) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, bool active) : Emotion(emotion), Strength(0.0f), bActive(active) {}
FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, float strength, bool active) : Emotion(emotion), Strength(strength), bActive(active) {}

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
};

FAIEmotionState::FAIEmotionState() {}
FAIEmotionState::FAIEmotionState(const FAISingleEmotionState& emotion) { Emotions.Add(emotion); }
FAIEmotionState::FAIEmotionState(const TArray<FAISingleEmotionState>& emotions) {	Emotions.Append(emotions); }