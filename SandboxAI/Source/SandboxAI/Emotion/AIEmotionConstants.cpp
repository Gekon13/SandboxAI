// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionConstants.h"

TMap<EEmotionName, FString> FAIEmotionConstants::EmotionNames = FAIEmotionConstants::BuildEmotionNamesMap();

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

	return emotionNames;
}