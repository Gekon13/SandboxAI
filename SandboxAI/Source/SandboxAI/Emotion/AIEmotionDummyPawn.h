// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIEmotionConstants.h"
#include "AIEmotionDummyPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class SANDBOXAI_API AAIEmotionDummyPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Pawn")
		UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Pawn")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		EEmotionSimpleValency Valency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		bool bContinuous;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion", meta=(ClampMin=0.0, ClampMax=1.0, UIMin=0.0, UIMax=1.0))
		float Value;

public:
	AAIEmotionDummyPawn();
	
};
