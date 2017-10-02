// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include <initializer_list>
#include "Emotion/Dummies/VisibleFriend.h"
#include "Emotion/Dummies/VisibleEnemy.h"
#include "AIEmotionKnowledge.h"

UAIEmotionKnowledge::UAIEmotionKnowledge()
{
	Scale = 1.0f;

	AvailableActionNames.Add(FString(TEXT("Run")));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::JoyfulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::DistressfulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) })));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::LovableGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Love_Hate, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::HatefulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Love_Hate, -0.5f) })));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::HopePromisingGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Hope_Fear, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::ScaryGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Hope_Fear, -0.5f) })));

	// this is from era befor gameplay component, might be useful in some cases
	//Informations.Add(FAIEmotionInformation(EEmotionActionName::See, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) }), FAIEmotionTarget(AVisibleFriend::StaticClass()) ));
	//Informations.Add(FAIEmotionInformation(EEmotionActionName::See, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) }), FAIEmotionTarget(AVisibleEnemy::StaticClass()) ));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) }), FAIEmotionTarget(ETeamType::FRIENDLY)));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) }), FAIEmotionTarget(ETeamType::ENEMY)));
}

void UAIEmotionKnowledge::SetScale(float newScale)
{
	float multiplier = 1.0f;
	if (Scale > KINDA_SMALL_NUMBER) // ensure for divisionBy0
	{
		multiplier = newScale / Scale;
	}
	else 
	{
		multiplier = 1.0f;
	}
	Scale = newScale;

	int32 informationNumber = Informations.Num();
	for (int32 informationIndex = 0; informationIndex < informationNumber; ++informationIndex)
	{
		int32 emotionDeltaNumber = Informations[informationIndex].EmotionDeltas.Num();

		for (int32 emotionDeltaIndex = 0; emotionDeltaIndex < emotionDeltaNumber; ++emotionDeltaIndex)
		{
			Informations[informationIndex].EmotionDeltas[emotionDeltaIndex].EmotionPairDelta *= multiplier;
		}
	}
}