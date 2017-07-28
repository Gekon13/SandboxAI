// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIPsiEmotionEngine.h"

FAIPsiEmotionEngine::FAIPsiEmotionEngine()
{
}

void FAIPsiEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge)
{
	Super::InitializeEmotionEngine(EmotionKnowledge);
}

void FAIPsiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);
}