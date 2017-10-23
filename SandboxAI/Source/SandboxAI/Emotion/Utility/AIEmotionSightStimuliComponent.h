// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AIEmotionSightStimuliComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UAIEmotionSightStimuliComponent : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()
	
public:
	UAIEmotionSightStimuliComponent(const FObjectInitializer & ObjectInitializer);
	
};
