// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Containers/AIEmotionConstants.h"
#include "AIEmotionDummyInterface.h"
#include "AIEmotionDummyPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECT_API AAIEmotionDummyPawn : public APawn, public IAIEmotionDummyInterface
{
	GENERATED_BODY()

public: // members

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		EEmotionSimpleValency Valency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		bool bContinuous;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion", meta=(ClampMin=0.0, ClampMax=1.0, UIMin=0.0, UIMax=1.0))
		float Value;

public: // methods
	AAIEmotionDummyPawn();
	
	virtual EEmotionSimpleValency GetValency_Implementation() override;
	virtual bool IsContinuous_Implementation() override;
	virtual float GetValue_Implementation() override;
};
