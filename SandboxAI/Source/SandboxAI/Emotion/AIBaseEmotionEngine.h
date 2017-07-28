// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIEmotionConstants.h"
#include "AIEmotionKnowledge.h"
#include "AIBaseEmotionEngine.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FAIBaseEmotionEngine
{
	GENERATED_BODY()

protected: //members
	FAIEmotionKnowledge* EmotionKnowledge;

public: //methods
	FAIBaseEmotionEngine();

	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge);
	virtual void TickEmotionEngine(float deltaSeconds);
	
	FORCEINLINE FAIEmotionKnowledge* GetEmotionKnowledge() const { return EmotionKnowledge; }
};