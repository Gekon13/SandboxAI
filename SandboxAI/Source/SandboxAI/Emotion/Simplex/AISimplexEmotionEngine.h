// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AISimplexEmotionEngine.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FAISimplexEmotionEngine : public FAIBaseEmotionEngine
{
	GENERATED_BODY()
public:
	
	FAISimplexEmotionEngine();
	
	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;
};