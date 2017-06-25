// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiStructures.h"

const float FWasabiConstants::WasabiSpaceRadius = 100.0f;
const float FWasabiConstants::FWasabiEmotionDefaultInnerRadius = 10.0f;
const float FWasabiConstants::FWasabiEmotionDefaultOuterRadius = 25.0f;
//const FString FWasabiConstants::ColumnSeparator = FString(TEXT(","));

#define ColumnSeparator FString(TEXT(","))

const FWasabiSpacePointPAD FWasabiSpacePointPAD::WasabiSpacePointPADMin = FWasabiSpacePointPAD( -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointPAD FWasabiSpacePointPAD::WasabiSpacePointPADMax = FWasabiSpacePointPAD(FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius);

const FWasabiSpacePointVMB FWasabiSpacePointVMB::WasabiSpacePointVMBMin = FWasabiSpacePointVMB(-FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointVMB FWasabiSpacePointVMB::WasabiSpacePointVMBMax = FWasabiSpacePointVMB(FWasabiConstants::WasabiSpaceRadius, FWasabiConstants::WasabiSpaceRadius, 0.0f);

const FWasabiSpacePointPADEmotion FWasabiSpacePointPADEmotion::Joy = FWasabiSpacePointPADEmotion(50.0f, 0.0f, -FWasabiConstants::WasabiSpaceRadius);
const FWasabiSpacePointPADEmotion FWasabiSpacePointPADEmotion::Distress = FWasabiSpacePointPADEmotion(-50.0f, 0.0f, -FWasabiConstants::WasabiSpaceRadius);

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

	result.Append(FString::Printf(TEXT("%d%s%d%s%d%s"), PAD.GetPleasure(), *separator, PAD.GetArousal(), *separator, PAD.GetDominance(), *separator));

	result.Append(FString::Printf(TEXT("%d%s%d%s%d%s"), VMB.GetValence(), *separator, VMB.GetMood(), *separator, VMB.GetBoredoom(), *separator));

	result.Append(FString::Printf(TEXT("%f"), InputValency));
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