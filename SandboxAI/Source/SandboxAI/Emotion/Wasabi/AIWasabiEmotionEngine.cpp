// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiEmotionEngine.h"

FAIWasabiEmotionEngine::FAIWasabiEmotionEngine()
{
}

void FAIWasabiEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* EmotionKnowledge)
{
	Super::InitializeEmotionEngine(EmotionKnowledge);
}

void FAIWasabiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{	
	Super::TickEmotionEngine(DeltaSeconds);
}