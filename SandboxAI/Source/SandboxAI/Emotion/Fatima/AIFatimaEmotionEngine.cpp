// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIFatimaEmotionEngine.h"

UAIFatimaEmotionEngine::UAIFatimaEmotionEngine()
{
	SomeName = TEXT("Fatima");
	SomeOtherName = TEXT("Fatima");
}

void UAIFatimaEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);
}

void UAIFatimaEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);
}

float UAIFatimaEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAIFatimaEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	// this method handles stuff like bonfires
}