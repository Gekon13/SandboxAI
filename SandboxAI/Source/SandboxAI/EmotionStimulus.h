// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIStructures.h"
#include "EmotionStimulus.generated.h"

//CannotImplementInterfaceInBlueprint
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UEmotionStimulus : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class SANDBOXAI_API IEmotionStimulus
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent)
		int32 GetEmotionStimulusElementCount() const;

	UFUNCTION(BlueprintNativeEvent)
		FEmotionStimulusElement GetEmotionStimulusElement(const int32& index) const;
};
