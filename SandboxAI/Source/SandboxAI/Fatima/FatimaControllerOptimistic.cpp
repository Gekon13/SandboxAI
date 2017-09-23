// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "FatimaControllerOptimistic.h"
#include "Emotion/AIEmotionComponent.h"


AFatimaControllerOptimistic::AFatimaControllerOptimistic() {
	bHandleSpeedAction = true;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Fatima;

	FFatimaEmotions Personality;
	Personality.JoyDistress.Amount = 0.45f;
	Personality.JoyDistress.DecayFactor = 0.3f;
	Personality.LoveHate.Amount = 0.75f;
	Personality.LoveHate.DecayFactor = 0.3f;
	EmotionComponent->GetFatimaEmotionEngine()->SetPersonality(Personality);
}
