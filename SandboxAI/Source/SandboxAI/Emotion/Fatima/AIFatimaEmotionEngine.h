// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AIFatimaEmotionEngine.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FAIFatimaEmotionEngine : public FAIBaseEmotionEngine
{
	GENERATED_BODY()
public:

	FAIFatimaEmotionEngine();

	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;
};