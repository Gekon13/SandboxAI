// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "EmotionStimulus.h"


// This function does not need to be modified.
UEmotionStimulus::UEmotionStimulus(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

// Add default functionality here for any IEmotionStimulus functions that are not pure virtual.

bool IEmotionStimulus::AffectOverTime() const
{
	return false;
}

float IEmotionStimulus::GetValency() const
{
	return 0.0f;
}