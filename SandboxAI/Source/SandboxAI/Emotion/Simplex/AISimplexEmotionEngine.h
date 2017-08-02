// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AISimplexStructures.h"
#include "AISimplexEmotionEngine.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAISimplexEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Personality")
		FSimplexPersonality Personality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		FSimplexPADPoint NeutralEmotionalState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		FSimplexPADPoint CurrentEmotionalState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		float DecayFactor;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeOtherName;

public:
	UAISimplexEmotionEngine();
	
	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);

	//Temporary, just for the backward compability with "old" SandboxAI emotion engines implementation
	void UpdateRunAction(float JoyDistress);
};