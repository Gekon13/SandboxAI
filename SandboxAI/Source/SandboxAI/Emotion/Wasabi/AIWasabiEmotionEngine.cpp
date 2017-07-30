// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiEmotionEngine.h"
#include "AIWasabiBaseEngineCore.h"
#include "AIWasabiOriginalEngineCore.h"

UAIWasabiEmotionEngine::UAIWasabiEmotionEngine()
{
	OriginalEngineCore = CreateDefaultSubobject<UAIWasabiOriginalEngineCore>(TEXT("OriginalEngineCore"));

	SomeName = TEXT("Wasabi");
	SomeOtherName = TEXT("Wasabi");
}

void UAIWasabiEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);

	EngineCore = OriginalEngineCore;
}

void UAIWasabiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{	
	Super::TickEmotionEngine(DeltaSeconds);

	if (GetEngineCore() != nullptr)
	{
		GetEngineCore()->Tick(DeltaSeconds);
	}
}

float UAIWasabiEmotionEngine::GetEngineScale() const
{
	return 100.0f;
}

void UAIWasabiEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	// this method handles stuff like bonfires
	if (GetEngineCore() != nullptr)
	{
		GetEngineCore()->Impulse(value);
	}
}