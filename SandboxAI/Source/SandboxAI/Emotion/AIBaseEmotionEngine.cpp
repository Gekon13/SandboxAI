// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIBaseEmotionEngine.h"

FAIBaseEmotionEngine::FAIBaseEmotionEngine()
{
}

void FAIBaseEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge)
{
	EmotionKnowledge = emotionKnowledge;
}
void FAIBaseEmotionEngine::TickEmotionEngine(float deltaSeconds)
{
}