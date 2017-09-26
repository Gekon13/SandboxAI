// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionState.h"

#define ColumnSeparator FString(TEXT(","))

FString FAISingleEmotionState::ToStringColumnNames()
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%s-Strength"), *FAIEmotionConstants::EmotionNames[Emotion]));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%s-IsActive"), *FAIEmotionConstants::EmotionNames[Emotion]));
	result.Append(separator);

	return result;
}
FString FAISingleEmotionState::ToStringLine()
{
	FString separator = ColumnSeparator;

	return FString::Printf(TEXT("%f%s%d%s"), Strength, *separator, bActive ? 1 : 0, *separator);
}

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

FString FAIEmotionState::ToStringColumnNames()
{
	FString result = FString();

	int32 emotionNumber = Emotions.Num();

	if (emotionNumber > 0)
	{
		for (int32 emotionIndex = 0; emotionIndex < emotionNumber; ++emotionIndex)
		{
			result.Append(Emotions[emotionIndex].ToStringColumnNames());
		}
	}

	return result;
}
FString FAIEmotionState::ToStringLine()
{
	FString result = FString();

	int32 emotionNumber = Emotions.Num();

	if (emotionNumber > 0)
	{
		for (int32 emotionIndex = 0; emotionIndex < emotionNumber; ++emotionIndex)
		{
			result.Append(Emotions[emotionIndex].ToStringLine());
		}
	}

	return result;
}