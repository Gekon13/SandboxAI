// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiBaseEngineCore.h"

UAIWasabiBaseEngineCore::UAIWasabiBaseEngineCore() :
	WasabiSpacePointPAD(FVector::ZeroVector)
{
}

void UAIWasabiBaseEngineCore::Initialize(const FWasabiCharacterTraits& characterTraits)
{
	MapCharacterTraitsToParams(characterTraits);
}
void UAIWasabiBaseEngineCore::Impulse(float value)
{
}
void UAIWasabiBaseEngineCore::Tick(float DeltaSeconds)
{
}

FWasabiEngineStepState UAIWasabiBaseEngineCore::GetWasabiEngineStepState() const
{
	return FWasabiEngineStepState();
}

void UAIWasabiBaseEngineCore::MapCharacterTraitsToParams(const FWasabiCharacterTraits& characterTraits)
{
}