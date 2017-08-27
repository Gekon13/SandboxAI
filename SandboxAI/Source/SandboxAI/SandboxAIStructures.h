// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIStructures.generated.h"

// use forward declarations
// don't include any headers in this file other than generated

class AActor;
class IEmotionStimulus;

/* 
In the engine there is a FStimulus struct.

Affecting - these stimulusses are percived and continiously affecting

EmotionStimulus - container

*/

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

UENUM(BlueprintType)
enum class EEmotionStimulusElementType : uint8
{
	// default
	EUnknown = 0 UMETA(DisplayName = "Unknown"),

	EPositive = 1 UMETA (DisplayName = "Positive"),
	ENegative = 2 UMETA(DisplayName = "Negative"),

	// this is PAD space - example. Add your own if needed, but always add, never remove.
	// in case of gr8 merge
	// (Filip - enum numbers starts with 1xx)
	// (Krzysztof- enum numbers starts with 2xx)
	// (Patryk - enum numbers starts with 3xx)
	// (Mateusz - enum numbers starts with 4xx)
	EPleasure = 101 UMETA(DisplayName = "Pleasure"),
	EArousal = 102 UMETA(DisplayName = "Arousal"),
	EDominance = 103 UMETA(DisplayName = "Dominance"),
	EValence = 104 UMETA(Display = "Valence"),
	EMood = 105 UMETA(Display = "Mood"),
	EBoredom = 106 UMETA(Display = "Boredom"),
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FCollisionProfiles
{
	GENERATED_BODY()
public:
	static const FName CharacterGhost;
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FEmotionStimulusElement
{
	GENERATED_BODY()
public:

	/** Type of affection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionStimulusElementType EmotionStimulusElementType;

	/** Whether affection is continious */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bContinious;

	/** Whether affection is continious */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Power;

public:
	FEmotionStimulusElement();
	FEmotionStimulusElement(EEmotionStimulusElementType EmotionStimulusElementType, bool bContinious, float Power);
};