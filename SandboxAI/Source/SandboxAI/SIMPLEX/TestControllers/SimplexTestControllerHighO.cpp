// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexTestControllerHighO.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "Emotion/Simplex/AISimplexStructures.h"


ASimplexTestControllerHighO::ASimplexTestControllerHighO() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Simplex;

	FSimplexPersonality& Personality = EmotionComponent->GetSimplexEmotionEngine()->Personality;
	Personality.OpennessToExperience = 0.6f;
}