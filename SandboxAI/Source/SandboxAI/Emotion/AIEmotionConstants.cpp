// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionConstants.h"

TMap<EEmotionName, FString> FAIEmotionConstants::EmotionNames = FAIEmotionConstants::BuildEmotionNamesMap();
TMap<EEmotionActionName, FString> FAIEmotionConstants::ActionNames = FAIEmotionConstants::BuildActionNamesMap();

TMap<EEmotionName, FString> FAIEmotionConstants::BuildEmotionNamesMap()
{
	TMap<EEmotionName, FString> emotionNames;

	emotionNames.Add(EEmotionName::None, TEXT("None"));

	emotionNames.Add(EEmotionName::Joy, TEXT("Joy"));
	emotionNames.Add(EEmotionName::Distress, TEXT("Distress"));

	emotionNames.Add(EEmotionName::Happyfor, TEXT("Happyfor"));
	emotionNames.Add(EEmotionName::Pitty, TEXT("Pitty"));

	emotionNames.Add(EEmotionName::Pride, TEXT("Pride"));
	emotionNames.Add(EEmotionName::Shame, TEXT("Shame"));

	emotionNames.Add(EEmotionName::Admiration, TEXT("Admiration"));
	emotionNames.Add(EEmotionName::Gloating, TEXT("Gloating"));

	emotionNames.Add(EEmotionName::Gratitude, TEXT("Gratitude"));
	emotionNames.Add(EEmotionName::Resentment, TEXT("Resentment"));

	emotionNames.Add(EEmotionName::Anger, TEXT("Anger"));
	emotionNames.Add(EEmotionName::Remorse, TEXT("Remorse"));

	emotionNames.Add(EEmotionName::Love, TEXT("Love"));
	emotionNames.Add(EEmotionName::Hate, TEXT("Hate"));

	emotionNames.Add(EEmotionName::Hope, TEXT("Hope"));
	emotionNames.Add(EEmotionName::Fear, TEXT("Fear"));

	emotionNames.Add(EEmotionName::Relief, TEXT("Relief"));
	emotionNames.Add(EEmotionName::FearsConfirmed, TEXT("Fears Confirmed"));

	emotionNames.Add(EEmotionName::Satisfaction, TEXT("Satisfaction"));
	emotionNames.Add(EEmotionName::Disapointment, TEXT("Disapointment"));

	emotionNames.Add(EEmotionName::Concentration, TEXT("Concentration"));
	emotionNames.Add(EEmotionName::Bore, TEXT("Bore"));

	emotionNames.Add(EEmotionName::WASABI_Angry, TEXT("Angry"));
	emotionNames.Add(EEmotionName::WASABI_Annoyed, TEXT("Annoyed"));
	emotionNames.Add(EEmotionName::WASABI_Bored, TEXT("Bored"));
	emotionNames.Add(EEmotionName::WASABI_Concentrated, TEXT("Concentrated"));
	emotionNames.Add(EEmotionName::WASABI_Depressed, TEXT("Depressed"));
	emotionNames.Add(EEmotionName::WASABI_Fearful, TEXT("Fearful"));
	emotionNames.Add(EEmotionName::WASABI_Happy, TEXT("Happy"));
	emotionNames.Add(EEmotionName::WASABI_Sad, TEXT("Sad"));
	emotionNames.Add(EEmotionName::WASABI_Surprised, TEXT("Surprised"));

	emotionNames.Add(EEmotionName::WASABI_Extended_Anxious, TEXT("Anxious"));

	return emotionNames;
}

TMap<EEmotionActionName, FString> FAIEmotionConstants::BuildActionNamesMap()
{
	TMap<EEmotionActionName, FString> actionNames;

	actionNames.Add(EEmotionActionName::None, TEXT("None"));

	actionNames.Add(EEmotionActionName::WalkTowards, TEXT("Walk towards"));
	actionNames.Add(EEmotionActionName::RunTowards, TEXT("Run towards"));
	actionNames.Add(EEmotionActionName::WalkAway, TEXT("Walk away"));
	actionNames.Add(EEmotionActionName::RunAway, TEXT("Run away"));
	actionNames.Add(EEmotionActionName::See, TEXT("See"));
	actionNames.Add(EEmotionActionName::UnSee, TEXT("Lost from sight"));

	actionNames.Add(EEmotionActionName::JoyfulGesture, TEXT("Joyful Gesture"));
	actionNames.Add(EEmotionActionName::DistressfulGesture, TEXT("Distressful Gesture"));

	actionNames.Add(EEmotionActionName::LovableGesture, TEXT("Lovable Gesture"));
	actionNames.Add(EEmotionActionName::HatefulGesture, TEXT("Hateful Gesture"));

	actionNames.Add(EEmotionActionName::HopePromisingGesture, TEXT("Hope promising Gesture"));
	actionNames.Add(EEmotionActionName::ScaryGesture, TEXT("Scary Gesture"));

	return actionNames;
}