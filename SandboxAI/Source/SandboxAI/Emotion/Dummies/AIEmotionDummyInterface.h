// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Common/AIEmotionConstants.h"
#include "AIEmotionDummyInterface.generated.h"

UINTERFACE(Blueprintable)
class PROJECT_API UAIEmotionDummyInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_API IAIEmotionDummyInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		EEmotionSimpleValency GetValency();
		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool IsContinuous();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		float GetValue();
};