// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiEmotionEngine.h"
#include "AIWasabiStructures.h"
#include "AIWasabiBaseEngineCore.h"
#include "AIWasabiOriginalEngineCore.h"

UAIWasabiEmotionEngine::UAIWasabiEmotionEngine()
{
	OriginalEngineCore = CreateDefaultSubobject<UAIWasabiOriginalEngineCore>(TEXT("OriginalEngineCore"));

	SomeName = TEXT("Wasabi");
	SomeOtherName = TEXT("Wasabi");
}

void UAIWasabiEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
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
		else
		{
			// just in case of division by 0 or number close to it...
			JoyDistressCoeficient = 0.5f;
			MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], JoyDistressCoeficient));
		}
	}
}

FAIEmotionState UAIWasabiEmotionEngine::GetEmotionState() const
{
	if (GetEngineCore() != nullptr)
	{
		return GetEngineCore()->GetEmotionState();
	}
	else
	{
		return FAIEmotionState();
	}
}

float UAIWasabiEmotionEngine::GetEngineScale() const
{
	return FWasabiConstants::WasabiSpaceRadius;
}

void UAIWasabiEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	// this method handles stuff like bonfires
	if (GetEngineCore() != nullptr)
	{
		GetEngineCore()->Impulse(value);
	}
}