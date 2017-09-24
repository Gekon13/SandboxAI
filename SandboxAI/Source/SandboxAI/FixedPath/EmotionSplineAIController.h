// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FixedPath/SandboxAISplineAIController.h"
#include "Emotion/Containers/AIEmotionConstants.h"
#include "Emotion/Containers/AIEmotionDecisionInfo.h"
#include "EmotionSplineAIController.generated.h"

class UAIEmotionComponent;

/**
 * 
 */
UCLASS()
class SANDBOXAI_API AEmotionSplineAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()
	
public: // members
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		UAIEmotionComponent* EmotionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		FString ActionWithSpeedCoeficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		FLinearColor MinColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		FLinearColor MaxColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		bool bHandleSpeedAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float Coeficient;

public: // methods
	AEmotionSplineAIController();
	
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

protected:
	UFUNCTION()
	void HandleDecisionMade(const FEmotionDecisionInfo& decisionInfo);
	void SetCoeficient(float coeficient);

};
