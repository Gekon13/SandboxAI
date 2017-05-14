// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EmotionStimulus.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
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
	
	/** Whether this emotional stimulus should affect agent over time */
	UFUNCTION()
	virtual bool AffectOverTime() const;

	/** Strength of the emotional stimulus, this can be positive or negative */
	UFUNCTION()
	virtual float GetValency() const;
};
