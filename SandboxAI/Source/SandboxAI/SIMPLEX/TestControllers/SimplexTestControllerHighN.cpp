// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexTestControllerHighN.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "Emotion/Simplex/AISimplexStructures.h"


ASimplexTestControllerHighN::ASimplexTestControllerHighN() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Simplex;

	FSimplexPersonality& Personality = EmotionComponent->GetSimplexEmotionEngine()->Personality;
	Personality.Neuroticism = 1.0f;
}