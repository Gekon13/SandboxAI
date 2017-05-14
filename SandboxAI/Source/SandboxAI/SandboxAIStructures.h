// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIStructures.generated.h"

class AActor;
class IEmotionStimulus;

/**
 *
 */
USTRUCT(BlueprintType)
struct SANDBOXAI_API FAffectingEmotionStimulus
{
	GENERATED_BODY()
public:
	/** Actor beeing source or parent of it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Actor;

	/** Pointer to emotion stimulus */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		IEmotionStimulus* EmotionStimulus;

public:
	FAffectingEmotionStimulus();
	FAffectingEmotionStimulus(AActor* Actor, IEmotionStimulus* EmotionStimulus);
};