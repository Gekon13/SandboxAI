// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEmotionConstants.h"
#include "AIEmotionKnowledge.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionKnowledge
{
	GENERATED_BODY()

public: //members // TODO: expand on this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		TArray<FString> AvailableActionNames;

public: //methods
	FAIEmotionKnowledge();

};