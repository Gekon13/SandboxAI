// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIPsiEmotionEngine.h"

UAIPsiEmotionEngine::UAIPsiEmotionEngine()
{
	SomeName = TEXT("Psi");
	SomeOtherName = TEXT("Psi");
}

void UAIPsiEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);
}

void UAIPsiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);
}

float UAIPsiEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAIPsiEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	// this method handles stuff like bonfires
}