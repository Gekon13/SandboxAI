// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AIFatimaEmotionEngine.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIFatimaEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeOtherName;

public:

	UAIFatimaEmotionEngine();

	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);
};