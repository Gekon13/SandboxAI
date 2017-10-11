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

	Informations.Add(FAIEmotionInformation(EEmotionActionName::JoyfulGesture, FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) ));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::DistressfulGesture, FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) ));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::LovableGesture, FAIEmotionDelta(EEmotionPairName::Love_Hate, 0.5f) ));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::HatefulGesture, FAIEmotionDelta(EEmotionPairName::Love_Hate, -0.5f) ));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::HopePromisingGesture, FAIEmotionDelta(EEmotionPairName::Hope_Fear, 0.5f) ));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::ScaryGesture, FAIEmotionDelta(EEmotionPairName::Hope_Fear, -0.5f) ));


	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) , FAIEmotionTarget(ETeamType::FRIENDLY)));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) , FAIEmotionTarget(ETeamType::ENEMY)));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::HearWalk, FAIEmotionTarget(ETeamType::FRIENDLY), FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f)));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::HearWalk, FAIEmotionTarget(ETeamType::ENEMY), FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f)));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::HearExplosion, FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f)));
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