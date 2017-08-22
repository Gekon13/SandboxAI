// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Emotion/AIEmotionConstants.h"
#include "AIWasabiAppraisal.generated.h"

class UAIWasabiBaseEngineCore;
class UAIEmotionKnowledge;

USTRUCT(BlueprintType)
struct SANDBOXAI_API FAIWasabiAppraisal
{
	GENERATED_BODY()

public:
	UAIWasabiBaseEngineCore* WasabiEngineCore;
	UAIEmotionKnowledge* Knowledge;
	UAIEmotionKnowledge* Memory;

public:
	FAIWasabiAppraisal();
	FAIWasabiAppraisal(UAIWasabiBaseEngineCore* wasabiEngineCore, UAIEmotionKnowledge* knowledge, UAIEmotionKnowledge* memory = nullptr);
	
	void AppraiseAction(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor);

};