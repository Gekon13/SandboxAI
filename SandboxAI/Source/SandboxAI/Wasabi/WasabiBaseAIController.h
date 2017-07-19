// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIBaseAIController.h"
#include "FixedPath/SandboxAISplineAIController.h"
#include "Wasabi/WasabiStructures.h"
#include "WasabiBaseAIController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SANDBOXAI_API AWasabiBaseAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()
	
protected:

	/** Emotion component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi")
		class UWasabiBaseEmotionComponent* WasabiEmotionComponent;

	/** Emotion component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi")
		FLinearColor MinColor;

	/** Emotion component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi")
		FLinearColor MaxColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logger")
		TArray<FWasabiEngineStepStateCGI> WasabiStates;

public:
	AWasabiBaseAIController();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement) override;

	FORCEINLINE TArray<FWasabiEngineStepStateCGI>* GetWasabiStepStates() { return &WasabiStates; }
};
