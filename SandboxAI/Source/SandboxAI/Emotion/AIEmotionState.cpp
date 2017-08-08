// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionState.h"

FString FAIEmotionState::ToString()
{
	FString resultString = FString();

	int32 emotionNumber = Emotions.Num();

	if (emotionNumber > 0)
	{
		resultString.Append(TEXT("Emotion State:"));
		resultString.Append(LINE_TERMINATOR);
		for (int32 emotionIndex = 0; emotionIndex < emotionNumber; ++emotionIndex)
		{
			resultString.Append(Emotions[emotionIndex].ToString());
			resultString.Append(LINE_TERMINATOR);
		}
	}
	else
	{
		resultString.Append(TEXT("No emotions in emotion string..."));
	}

	return resultString;
}