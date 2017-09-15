// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexControllerPesimist.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "Emotion/Simplex/AISimplexStructures.h"


ASimplexControllerPesimist::ASimplexControllerPesimist() : Super()
{
	bHandleSpeedAction = true;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Simplex;

	FSimplexPersonality& Personality = EmotionComponent->GetSimplexEmotionEngine()->Personality;
	Personality.Extraversion = -0.5f;
	Personality.Neuroticism = 0.5f;
	Personality.Conscientiousness = 0;
	Personality.OpennessToExperience = 0;
}