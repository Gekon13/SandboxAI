// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionActionInfo.h"

FEmotionActionInfo::FEmotionActionInfo()
	: ActionName(TEXT("")), ActionFValue(0.0f), ActionIValue(0), Emotion(EEmotionPrimary::None)
{
}

FEmotionActionInfo::FEmotionActionInfo(FString actionName, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(0.0f), ActionIValue(0), Emotion(emotion)
{
}
FEmotionActionInfo::FEmotionActionInfo(FString actionName, float value, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(value), ActionIValue(0), Emotion(emotion)
{
}
FEmotionActionInfo::FEmotionActionInfo(FString actionName, int32 value, EEmotionPrimary emotion)
	: ActionName(actionName), ActionFValue(0.0f), ActionIValue(value), Emotion(emotion)
{
}