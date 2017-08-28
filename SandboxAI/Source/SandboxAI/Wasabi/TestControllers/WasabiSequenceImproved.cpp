// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiSequenceImproved.h"


AWasabiSequenceImproved::AWasabiSequenceImproved() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Wasabi;
	EmotionComponent->GetWasabiEmotionEngine()->SetWasabiCoreType(EWasabiCoreType::Improved);

	EmotionComponent->GetWasabiEmotionEngine()->SetLogWasabiState(true);

	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Concentrated);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Anxious);
}

