// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AIEmotionConstants.h"
#include "AIEmotionInformation.h"
#include "AIEmotionKnowledge.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIEmotionKnowledge : public UObject
{
	GENERATED_BODY()

public: //members // TODO: expand on this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		TArray<FString> AvailableActionNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		TArray<FAIEmotionInformation> Informations;

public: //methods
	UAIEmotionKnowledge();

};