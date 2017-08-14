// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEmotionConstants.h"
#include "AIEmotionVisibleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIEmotionVisibleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SANDBOXAI_API IAIEmotionVisibleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FEmotionActionPerformed OnEmotionActionPerformed;

protected:
	UFUNCTION(BlueprintNativeEvent)
		void NotifyOnEmotionActionPerformed(EEmotionActionName emotionActionName, AActor* sourceActor = nullptr, AActor* targetActor = nullptr);

};
