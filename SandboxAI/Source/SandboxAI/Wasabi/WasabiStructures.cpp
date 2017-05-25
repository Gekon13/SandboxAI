// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiStructures.h"

const float FWasabiConstants::WasabiSpaceRadius = 100.0f;
const float FWasabiConstants::FWasabiEmotionDefaultInnerRadius = 10.0f;
const float FWasabiConstants::FWasabiEmotionDefaultOuterRadius = 25.0f;

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