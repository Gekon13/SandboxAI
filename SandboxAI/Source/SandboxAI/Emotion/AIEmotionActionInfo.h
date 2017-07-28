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

	/* Emotion that was cause of the action, for potential visual perposes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionPrimary Emotion;
public:

	FEmotionActionInfo();
};