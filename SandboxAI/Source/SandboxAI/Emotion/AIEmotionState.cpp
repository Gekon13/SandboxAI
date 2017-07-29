// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionState.h"

FAISingleEmotionState::FAISingleEmotionState() 
	: Emotion(EEmotionPrimary::None), Strength(0.0f), bActive(false)
{
}

FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion)
	: Emotion(emotion), Strength(0.0f), bActive(false)
{
}

FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, float strength)
	: Emotion(emotion), Strength(strength), bActive(false)
{
}

FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, bool active)
	: Emotion(emotion), Strength(0.0f), bActive(active)
{
}

FAISingleEmotionState::FAISingleEmotionState(EEmotionPrimary emotion, float strength, bool active)
	: Emotion(emotion), Strength(strength), bActive(active)
{
}


FAIEmotionState::FAIEmotionState()
{
}
FAIEmotionState::FAIEmotionState(const FAISingleEmotionState& emotion)
{
	Emotions.Add(emotion);
}
FAIEmotionState::FAIEmotionState(const TArray<FAISingleEmotionState>& emotions)
{
	Emotions.Append(emotions);
}