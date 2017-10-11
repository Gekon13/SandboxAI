// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "FatimaControllerNeutral.h"
#include "Emotion/AIEmotionComponent.h"


AFatimaControllerNeutral::AFatimaControllerNeutral() {
	bHandleSpeedAction = true;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Fatima;

	FFatimaEmotions Personality;
	Personality.JoyDistress.Amount = 0.f;
	Personality.JoyDistress.DecayFactor = 0.3f;
	/*Personality.LoveHate.Amount = 0.f;
	Personality.LoveHate.DecayFactor = 0.1f;
	Personality.HopeFear.Amount = 0.f;
	Personality.HopeFear.DecayFactor = 0.22f;*/
	EmotionComponent->GetFatimaEmotionEngine()->SetPersonality(Personality);
}
