// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include <initializer_list>
#include "AIEmotionKnowledge.h"

UAIEmotionKnowledge::UAIEmotionKnowledge()
{
	AvailableActionNames.Add(FString(TEXT("Run")));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::JoyfulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::DistressfulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) })));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::LovableGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Love_Hate, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::HatefulGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Love_Hate, -0.5f) })));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::HopePromisingGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Hope_Fear, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::ScaryGesture, std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Hope_Fear, -0.5f) })));

	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, FAIEmotionTarget(AActor::StaticClass(), FName("Friend")), std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, 0.5f) })));
	Informations.Add(FAIEmotionInformation(EEmotionActionName::See, FAIEmotionTarget(AActor::StaticClass(), FName("Enemy")), std::initializer_list<FAIEmotionDelta>({ FAIEmotionDelta(EEmotionPairName::Joy_Distress, -0.5f) })));
}