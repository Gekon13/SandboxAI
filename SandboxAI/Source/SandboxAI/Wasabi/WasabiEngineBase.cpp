// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiEngineBase.h"

UWasabiEngineBase::UWasabiEngineBase() :
	WasabiSpacePointPAD(FVector::ZeroVector)
{
}

UWasabiEngineBase::UWasabiEngineBase(const FWasabiSpacePointPAD& startSpacePointPAD) :
	WasabiSpacePointPAD(startSpacePointPAD)
{
}

void UWasabiEngineBase::Impulse(float value)
{
}
void UWasabiEngineBase::Tick(float DeltaSeconds)
{
}