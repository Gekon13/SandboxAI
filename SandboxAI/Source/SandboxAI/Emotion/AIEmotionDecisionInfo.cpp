// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionDecisionInfo.h"

FEmotionDecisionInfo::FEmotionDecisionInfo()
	: ActionName(TEXT("")), ActionFValue(0.0f), ActionIValue(0), Emotion(EEmotionPrimary::None)
{
}

FEmotionDecisionInfo::FEmotionDecisionInfo(FString actionName, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(0.0f), ActionIValue(0), Emotion(emotion)
{
}
FEmotionDecisionInfo::FEmotionDecisionInfo(FString actionName, float value, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(value), ActionIValue(0), Emotion(emotion)
{
}
FEmotionDecisionInfo::FEmotionDecisionInfo(FString actionName, int32 value, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(0.0f), ActionIValue(value), Emotion(emotion)
{
}