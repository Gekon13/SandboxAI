// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AISimplexStructures.h"
#include "AISimplexEmotionEngine.generated.h"

class UAISimplexAppraisalModule;
class UAIEmotionKnowledge;

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

	UPROPERTY(Instanced, VisibleAnywhere, Category = "Emotions")
		UAISimplexAppraisalModule* AppraisalModule;
	UPROPERTY(Instanced, VisibleAnywhere, Category = "Emotions")
		UAIEmotionKnowledge* Memory;

public:
	UAISimplexEmotionEngine();
	
	virtual void InitializeEmotionEngine(UAIEmotionKnowledge* InEmotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

	UFUNCTION()
	virtual void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor) override;

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float Value, bool bContinuous);

	//Temporary, just for the backward compability with "old" SandboxAI emotion engines implementation
	void UpdateRunAction(float JoyDistress);
};