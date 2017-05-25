// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAIStructures.h"

FAffectingEmotionStimulus::FAffectingEmotionStimulus() : 
	Actor(nullptr), 
	EmotionStimulus(nullptr)
{
}
FAffectingEmotionStimulus::FAffectingEmotionStimulus(AActor* Actor, IEmotionStimulus* EmotionStimulus) :
	Actor(Actor),
	EmotionStimulus(EmotionStimulus)
{
}

FEmotionStimulusElement::FEmotionStimulusElement() :
	EmotionStimulusElementType(EEmotionStimulusElementType::EUnknown),
	bContinious(true),
	Power(0.0f)
{
}
FEmotionStimulusElement::FEmotionStimulusElement(EEmotionStimulusElementType EmotionStimulusElementType, bool bContinious, float Power) :
	EmotionStimulusElementType(EmotionStimulusElementType),
	bContinious(bContinious),
	Power(Power)
{
}

const FName FCollisionProfiles::CharacterGhost = FName(TEXT("CharacterGhost"));