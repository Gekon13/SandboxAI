// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "EmotionSplineAIControllerOne.h"


AEmotionSplineAIControllerOne::AEmotionSplineAIControllerOne() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Wasabi;
	EmotionComponent->GetWasabiEmotionEngine()->SetWasabiCoreType(EWasabiCoreType::Original);
}

