// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexTestControllerLowE.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "Emotion/Simplex/AISimplexStructures.h"


ASimplexTestControllerLowE::ASimplexTestControllerLowE() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Simplex;

	FSimplexPersonality& Personality = EmotionComponent->GetSimplexEmotionEngine()->Personality;
	Personality.Extraversion = -0.6f;
}
