// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiStructures.h"

const float FWasabiConstants::WasabiSpaceRadius = 100.0f;
const float FWasabiConstants::FWasabiEmotionDefaultInnerRadius = 10.0f;
const float FWasabiConstants::FWasabiEmotionDefaultOuterRadius = 25.0f;
//const FString FWasabiConstants::ColumnSeparator = FString(TEXT(","));

#define ColumnSeparator FString(TEXT(","))

const FWasabiSpacePointPAD FWasabiSpacePointPAD::WasabiSpacePointPADMin = FWasabiSpacePointPAD( -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointPAD FWasabiSpacePointPAD::WasabiSpacePointPADMax = FWasabiSpacePointPAD(FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius);

const FWasabiSpacePointVMB FWasabiSpacePointVMB::WasabiSpacePointVMBMin = FWasabiSpacePointVMB(-FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointVMB FWasabiSpacePointVMB::WasabiSpacePointVMBMax = FWasabiSpacePointVMB(FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius, 0.0f);

const FWasabiSpacePointPADEmotion FWasabiSpacePointPADEmotion::MockJoy = FWasabiSpacePointPADEmotion(FWasabiConstants::WasabiSpaceRadius * 0.5f, 0.0f, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointPADEmotion FWasabiSpacePointPADEmotion::MockDistress = FWasabiSpacePointPADEmotion(-FWasabiConstants::WasabiSpaceRadius * 0.5f, 0.0f, -FWasabiConstants::WasabiSpaceRadius);

void FWasabiSpacePointPAD::ClampPleasureBySpace()
{
	X = FMath::Clamp<float>(X, WasabiSpacePointPADMin.X, WasabiSpacePointPADMin.X);
}
void FWasabiSpacePointPAD::ClampArousalBySpace()
{
	Y = FMath::Clamp<float>(Y, WasabiSpacePointPADMin.Y, WasabiSpacePointPADMin.Y);
}
void FWasabiSpacePointPAD::ClampDominanceBySpace()
{
	Z = FMath::Clamp<float>(Z, WasabiSpacePointPADMin.Z, WasabiSpacePointPADMin.Z);
}

void FWasabiSpacePointVMB::ClampValenceBySpace()
{
	X = FMath::Clamp<float>(X, WasabiSpacePointVMBMin.X, WasabiSpacePointVMBMax.X);
}
void FWasabiSpacePointVMB::ClampMoodBySpace()
{
	Y = FMath::Clamp<float>(Y, WasabiSpacePointVMBMin.Y, WasabiSpacePointVMBMax.Y);
}
void FWasabiSpacePointVMB::ClampBoredoomBySpace()
{
	Z = FMath::Clamp<float>(Z, WasabiSpacePointVMBMin.Z, WasabiSpacePointVMBMax.Z);
}

void FWasabiEmotion::UpdateEmotion(const FWasabiSpacePointPAD& wasabiSpacePointPAD)
{
	float smallestDistance = HUGE_VALF;
	int32 emotionSpacePointIndexWithSmallestDistance = -1;

	int32 emotionSpacePointNumber = EmotionSpacePoints.Num();
	for (int32 emotionSpacePointIndex = 0; emotionSpacePointIndex < emotionSpacePointNumber; ++emotionSpacePointIndex)
	{
		float distance = FWasabiSpacePointPAD::Distance(wasabiSpacePointPAD, EmotionSpacePoints[emotionSpacePointIndex]);
		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			emotionSpacePointIndexWithSmallestDistance = emotionSpacePointIndex;
		}
	}

	if (emotionSpacePointIndexWithSmallestDistance != -1)
	{
		if (bActive)
		{
			if (smallestDistance > EmotionSpacePoints[emotionSpacePointIndexWithSmallestDistance].GetOuterRadius())
			{
				bActive = false;
			}
		}
		else
		{
			if (smallestDistance <= EmotionSpacePoints[emotionSpacePointIndexWithSmallestDistance].GetInnerRadius())
			{
				bActive = true;
			}
		}
	}
	else
	{
		bActive = false;
	}

	if (bActive)
	{
		const float innerRadius = EmotionSpacePoints[emotionSpacePointIndexWithSmallestDistance].GetInnerRadius();

		if (smallestDistance <= innerRadius)
		{
			Strength = FWasabiConstants::WasabiSpaceRadius;
		}
		else
		{
			const float outerRadius = EmotionSpacePoints[emotionSpacePointIndexWithSmallestDistance].GetOuterRadius();
			
			Strength = ((smallestDistance - innerRadius) / (outerRadius - innerRadius)) * FWasabiConstants::WasabiSpaceRadius;
		}
	}
	else
	{
		Strength = 0.0f;
	}
}

FString FWasabiEngineStepState::ToStringColumnNames()
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(TEXT("Index"));
	result.Append(separator);

	result.Append(TEXT("Pleasure"));
	result.Append(separator);

	result.Append(TEXT("Arousal"));
	result.Append(separator);

	result.Append(TEXT("Dominance"));
	result.Append(separator);

	result.Append(TEXT("Valence"));
	result.Append(separator);

	result.Append(TEXT("Mood"));
	result.Append(separator);

	result.Append(TEXT("Boredoom"));
	result.Append(separator);

	result.Append(TEXT("InputValency"));
	result.Append(separator);

	return result;
}
FString FWasabiEngineStepState::ToStringLine()
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%d"),Index));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), PAD.X, *separator, PAD.Y, *separator, PAD.Z, *separator));

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), VMB.X, *separator, VMB.Y, *separator, VMB.Z, *separator));

	result.Append(FString::Printf(TEXT("%f"), InputValency));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepState::ToStringLineOverrideInputValency(float inputValency)
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%d"), Index));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), PAD.X, *separator, PAD.Y, *separator, PAD.Z, *separator));

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), VMB.X, *separator, VMB.Y, *separator, VMB.Z, *separator));

	result.Append(FString::Printf(TEXT("%f"), inputValency));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepStateCGI::ToStringColumnNames()
{
	FString result = Super::ToStringColumnNames();

	FString separator = ColumnSeparator;

	result.Append(TEXT("Joy"));
	result.Append(separator);

	result.Append(TEXT("Distress"));
	result.Append(separator);

	result.Append(TEXT("DistanceCovered"));
	result.Append(separator);

	result.Append(TEXT("Speed"));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepStateCGI::ToStringLine()
{
	FString result = Super::ToStringLine();

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%f"), Joy));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Distress));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), DistanceCovered));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Speed));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepStateCGI::ToStringLineOverrideInputValency(float inputValency)
{
	FString result = Super::ToStringLineOverrideInputValency(inputValency);

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%f"), Joy));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Distress));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), DistanceCovered));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Speed));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepStateCGI::ToStringColumnNamesCustom()
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(TEXT("Index"));
	result.Append(separator);

	result.Append(TEXT("DistanceCovered"));
	result.Append(separator);

	result.Append(TEXT("Pleasure"));
	result.Append(separator);

	result.Append(TEXT("Arousal"));
	result.Append(separator);

	result.Append(TEXT("Dominance"));
	result.Append(separator);

	result.Append(TEXT("Valence"));
	result.Append(separator);

	result.Append(TEXT("Mood"));
	result.Append(separator);

	result.Append(TEXT("Boredoom"));
	result.Append(separator);

	result.Append(TEXT("InputValency"));
	result.Append(separator);

	result.Append(TEXT("Joy"));
	result.Append(separator);

	result.Append(TEXT("Distress"));
	result.Append(separator);

	result.Append(TEXT("Speed"));
	result.Append(separator);

	return result;
}

FString FWasabiEngineStepStateCGI::ToStringLineCustom(float inputValency)
{
	FString result = FString();

	FString separator = ColumnSeparator;

	result.Append(FString::Printf(TEXT("%d"), Index));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), DistanceCovered));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), PAD.X, *separator, PAD.Y, *separator, PAD.Z, *separator));

	result.Append(FString::Printf(TEXT("%f%s%f%s%f%s"), VMB.X, *separator, VMB.Y, *separator, VMB.Z, *separator));

	result.Append(FString::Printf(TEXT("%f"), inputValency));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Joy));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Distress));
	result.Append(separator);

	result.Append(FString::Printf(TEXT("%f"), Speed));
	result.Append(separator);

	return result;
}