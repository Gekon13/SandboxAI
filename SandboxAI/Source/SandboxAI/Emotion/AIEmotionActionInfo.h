// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEmotionConstants.h"
#include "AIEmotionActionInfo.generated.h"

/// Info about action that emotion component decided to take
USTRUCT(BlueprintType)
struct PROJECT_API FEmotionActionInfo
{
	GENERATED_BODY()
public:

	/* Name of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ActionName;

	/* Float value of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ActionFValue;

	/* Int value of the action */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ActionIValue;

	/* Emotion that was cause of the action, for potential visual perposes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionPrimary Emotion;
public:

	FEmotionActionInfo();
	FEmotionActionInfo(FString actionName, EEmotionPrimary emotion = EEmotionPrimary::None);
	FEmotionActionInfo(FString actionName, float value, EEmotionPrimary emotion = EEmotionPrimary::None);
	FEmotionActionInfo(FString actionName, int32 value, EEmotionPrimary emotion = EEmotionPrimary::None);
};