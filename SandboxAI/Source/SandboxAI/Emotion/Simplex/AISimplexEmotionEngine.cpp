// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexEmotionEngine.h"

FAISimplexEmotionEngine::FAISimplexEmotionEngine()
{
}

void FAISimplexEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge)
{
	Super::InitializeEmotionEngine(EmotionKnowledge);
}

void FAISimplexEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);
}