// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIEmotionConstants.h"
#include "AIBaseEmotionEngine.generated.h"

class FAIEmotionKnowledge;

USTRUCT(BlueprintType)
struct PROJECT_API FAIBaseEmotionEngine
{
	GENERATED_BODY()

public: //members
	FAIEmotionKnowledge* EmotionKnowledge;

public: //methods
	FAIBaseEmotionEngine();

	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge) = 0;
	virtual void TickEmotionEngine(float DeltaSeconds) = 0;
};