// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Common/AIEmotionKnowledge.h"
#include "PsiStructures.h"
#include "AIPsiEmotionKnowledge.generated.h"

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiKnowledge
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EPsiDrive Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		FString Action;

	FPsiKnowledge()
	{
		Type = EPsiDrive::ENone;
		Action = "";
	}

	FPsiKnowledge(EPsiDrive drive, FString action)
	{
		Type = drive;
		Action = action;
	}
};

UCLASS()
class SANDBOXAI_API UAIPsiEmotionKnowledge : public UAIEmotionKnowledge
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		TArray<FPsiKnowledge> Actions;

	UAIPsiEmotionKnowledge();
};
