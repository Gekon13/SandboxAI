// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIBaseEmotionEngine.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AIPerceptionSystem.h"

UAIBaseEmotionEngine::UAIBaseEmotionEngine()
{
}

void UAIBaseEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	EmotionKnowledge = emotionKnowledge;
}
void UAIBaseEmotionEngine::TickEmotionEngine(float deltaSeconds)
{
}

FAIEmotionState UAIBaseEmotionEngine::GetEmotiomState() const
{
	return FAIEmotionState();
}

float UAIBaseEmotionEngine::GetEngineScale() const
{
	return 100.0f;
}

void UAIBaseEmotionEngine::DirectValencedImpulse(float value, bool bContinuous)
{
	DirectValencedImpulseInternal(value * GetEngineScale(), bContinuous);
}

void UAIBaseEmotionEngine::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

}

void UAIBaseEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
}

void UAIBaseEmotionEngine::MakeDecision(const FEmotionDecisionInfo& decisionInfo)
{
	OnPassDecision.Execute(decisionInfo);
}