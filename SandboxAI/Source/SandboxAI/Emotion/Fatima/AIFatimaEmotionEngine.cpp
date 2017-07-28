// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIFatimaEmotionEngine.h"

FAIFatimaEmotionEngine::FAIFatimaEmotionEngine()
{
}

void FAIFatimaEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge)
{
	Super::InitializeEmotionEngine(EmotionKnowledge);
}

void FAIFatimaEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);
}