// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Emotions.generated.h"

USTRUCT()
struct FEmotion
{
	GENERATED_BODY()

public:
	FEmotion() : FEmotion("Test") {}
	FEmotion(FString Name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float DecayFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		FString Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float AmountAfterEvent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float TimeOfEvent;

	bool bContinuous;
};

USTRUCT()
struct FEmotions
{
	GENERATED_BODY()

public:
	FEmotions();
	FEmotion* FindEmotionWithName(FString Name);

	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion JoyDistress;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion HappyforResentment;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion GloatingPity;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion PrideShame;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion AdmirationReproach;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion GratificationRemorse;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion GratitudeAnger;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion LoveHate;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion HopeFear;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion ReliefDisappointment;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FEmotion SatisfactionFearsconfirmed;

};
