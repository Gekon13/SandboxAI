// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AIWasabiEmotionEngine.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FAIWasabiEmotionEngine : public FAIBaseEmotionEngine
{
	GENERATED_BODY()
public:
	
	FAIWasabiEmotionEngine();
	
	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;
};