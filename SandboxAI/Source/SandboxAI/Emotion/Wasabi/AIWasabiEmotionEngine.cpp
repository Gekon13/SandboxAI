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

		const FWasabiSpacePointPAD currentSpacePointPAD = GetEngineCore()->GetWasabiSpacePointPAD();

		JoyDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::Joy);
		DistressDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::Distress);

		if (JoyDistance > SMALL_NUMBER || DistressDistance > SMALL_NUMBER)
		{
			float coeficient = FMath::Clamp( JoyDistance / (JoyDistance + DistressDistance), 0.0f, 1.0f);

			if (coeficient != JoyDistressCoeficient)
			{
				JoyDistressCoeficient = coeficient;
				MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], JoyDistressCoeficient));
			}
		}
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