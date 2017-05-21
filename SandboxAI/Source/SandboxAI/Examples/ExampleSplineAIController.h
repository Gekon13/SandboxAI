// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FixedPath/SandboxAISplineAIController.h"
#include "ExampleSplineAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API AExampleSplineAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float EmotionValence;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emotion")
		float EmotionValenceMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emotion")
		float EmotionValenceMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emotion")
		float EmotionValenceNullifyRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emotion")
		FLinearColor EmotionColorMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Emotion")
		FLinearColor EmotionColorMax;

public:
	AExampleSplineAIController();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement) override;

protected:
	void UpdateActorEmotionalStateConsequences();
};
