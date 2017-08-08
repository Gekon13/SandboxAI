// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiBaseEngineCore.h"

UAIWasabiBaseEngineCore::UAIWasabiBaseEngineCore() :
	WasabiSpacePointPAD(FVector::ZeroVector)
{

}

void UAIWasabiBaseEngineCore::Initialize()
{
}
void UAIWasabiBaseEngineCore::Impulse(float value)
{
}
void UAIWasabiBaseEngineCore::Tick(float DeltaSeconds)
{
}

void UAIWasabiBaseEngineCore::AddEmotionToEngine(const FWasabiEmotion& wasabiEmotion)
{
	KnownEmotions.Add(wasabiEmotion);
}

FAIEmotionState UAIWasabiBaseEngineCore::GetEmotionState(bool onlyActiveEmotions) const
{
	FAIEmotionState resultEmotionState;

	int32 knownEmotionNumber = KnownEmotions.Num();
	if (onlyActiveEmotions)
	{
		for (int32 knownEmotionIndex = 0; knownEmotionIndex < knownEmotionNumber; ++knownEmotionIndex)
		{
			if (KnownEmotions[knownEmotionIndex].bActive)
			{
				resultEmotionState.Emotions.Add(KnownEmotions[knownEmotionIndex].ToSingleEmotionState());
			}
		}
	}
	else
	{
		for (int32 knownEmotionIndex = 0; knownEmotionIndex < knownEmotionNumber; ++knownEmotionIndex)
		{
			resultEmotionState.Emotions.Add(KnownEmotions[knownEmotionIndex].ToSingleEmotionState());
		}
	}

	return resultEmotionState;
}