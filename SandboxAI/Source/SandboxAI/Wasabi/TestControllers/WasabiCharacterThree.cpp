// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiCharacterThree.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"

AWasabiCharacterThree::AWasabiCharacterThree() : Super()
{
	bHandleSpeedAction = false;
	EmotionComponent->EmotionEngineModel = EEmotionEngineModel::Wasabi;
	EmotionComponent->GetWasabiEmotionEngine()->SetWasabiCoreType(EWasabiCoreType::Improved);

	EmotionComponent->GetWasabiEmotionEngine()->SetLogWasabiState(true);

	FWasabiCharacterTraits characterTraits;
	characterTraits.Extraversion = 0.0f;
	characterTraits.Agreeableness = 0.0f;
	characterTraits.Conscientiousness = 0.0f;
	characterTraits.EmotionalStability = 0.5f;
	characterTraits.Sophistication = 0.0f;
	EmotionComponent->GetWasabiEmotionEngine()->SetCharacterTraits(characterTraits);

#ifdef WASABI_EMOTIONS_HAPPY_ANGRY
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Angry);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Annoyed);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Depressed);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Fearful);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Happy);
#endif

#ifdef WASABI_EMOTIONS_ALL
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Angry);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Annoyed);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Bored);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Concentrated);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Depressed);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Fearful);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Happy);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Sad);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Surprised);
	EmotionComponent->GetWasabiEmotionEngine()->AddEmotion(WasabiEmotions::Anxious);
#endif
}

