// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiEmotionEngine.h"
#include "AIWasabiStructures.h"
#include "AIWasabiBaseEngineCore.h"
#include "AIWasabiOriginalEngineCore.h"
#include "AIWasabiImprovedEngineCore.h"

#define TEST_0
//#define TEST_1
//#define TEST_ALL

UAIWasabiEmotionEngine::UAIWasabiEmotionEngine() :
	WasabiAppraisal(FAIWasabiAppraisal()),
	CharacterTraits(FWasabiCharacterTraits())
{
	OriginalEngineCore = CreateDefaultSubobject<UAIWasabiOriginalEngineCore>(TEXT("OriginalEngineCore"));
	ImprovedEngineCore = CreateDefaultSubobject<UAIWasabiImprovedEngineCore>(TEXT("ImprovedEngineCore"));

	WasabiCoreType = EWasabiCoreType::Original;
#if  defined(TEST_0) ||  defined(TEST_1) || defined(TEST_ALL)
	bLogWasabiState = true;
#else
	bLogWasabiState = false;
#endif

	_timeElapsed = 0.0f;
}

void UAIWasabiEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);

	switch (WasabiCoreType)
	{
	case EWasabiCoreType::Original:
		EngineCore = OriginalEngineCore;
		break;
	case EWasabiCoreType::Improved:
		EngineCore = ImprovedEngineCore;
		break;
	}

#if  defined(TEST_0) ||  defined(TEST_1) || defined(TEST_ALL)
	bLogWasabiState = true;
#else
	bLogWasabiState = false;
#endif

#ifdef TEST_0
	KnownEmotions.Add(WasabiEmotions::Concentrated);
	KnownEmotions.Add(WasabiEmotions::Anxious);
#endif

#ifdef TEST_1
	KnownEmotions.Add(WasabiEmotions::Angry);
	KnownEmotions.Add(WasabiEmotions::Annoyed);
	KnownEmotions.Add(WasabiEmotions::Depressed);
	KnownEmotions.Add(WasabiEmotions::Fearful);
	KnownEmotions.Add(WasabiEmotions::Happy);
#endif

#ifdef TEST_ALL
	KnownEmotions.Add(WasabiEmotions::Angry);
	KnownEmotions.Add(WasabiEmotions::Annoyed);
	KnownEmotions.Add(WasabiEmotions::Bored);
	KnownEmotions.Add(WasabiEmotions::Concentrated);
	KnownEmotions.Add(WasabiEmotions::Depressed);
	KnownEmotions.Add(WasabiEmotions::Fearful);
	KnownEmotions.Add(WasabiEmotions::Happy);
	KnownEmotions.Add(WasabiEmotions::Sad);
	KnownEmotions.Add(WasabiEmotions::Surprised);
	KnownEmotions.Add(WasabiEmotions::Anxious);
#endif

	if (GetEngineCore() != nullptr)
	{
		GetEngineCore()->Initialize(CharacterTraits);
	}

	_timeElapsed = 0.0f;
	WasabiAppraisal.Initialize(EngineCore, emotionKnowledge, nullptr);
}

void UAIWasabiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{	
	Super::TickEmotionEngine(DeltaSeconds);

	if (GetEngineCore() != nullptr)
	{
		_timeElapsed += DeltaSeconds;
		GetEngineCore()->Tick(DeltaSeconds);

		const FWasabiSpacePointPAD currentSpacePointPAD = GetEngineCore()->GetWasabiSpacePointPAD();

		JoyDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::MockJoy);
		DistressDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::MockDistress);

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

		int32 knownEmotionNumber = KnownEmotions.Num();
		for (int32 knownEmotionIndex = 0; knownEmotionIndex < knownEmotionNumber; ++knownEmotionIndex)
		{
			KnownEmotions[knownEmotionIndex].UpdateEmotionNoDominance(currentSpacePointPAD);
		}

		if (bLogWasabiState)
		{
			WasabiStates.Add(GetWasabiComplexStepState());
		}
	}
}

FAIEmotionState UAIWasabiEmotionEngine::GetEmotionState() const
{
	FAIEmotionState resultEmotionState;

	int32 knownEmotionNumber = KnownEmotions.Num();
	for (int32 knownEmotionIndex = 0; knownEmotionIndex < knownEmotionNumber; ++knownEmotionIndex)
	{
		resultEmotionState.Emotions.Add(KnownEmotions[knownEmotionIndex].ToSingleEmotionState());
	}

	return resultEmotionState;
}

void UAIWasabiEmotionEngine::HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor)
{
	// handle action perception
	UE_LOG(LogTemp, Log, TEXT("[%s]Perceived action: %s, source: %s, target %s"), *EmotionKnowledge->ControlledActor->GetName(), *FAIEmotionConstants::ActionNames[EmotionActionName], sourceActor != nullptr ? *sourceActor->GetName() : TEXT("None"), targetActor != nullptr ? *targetActor->GetName() : TEXT("None"));

	WasabiAppraisal.AppraiseAction(EmotionActionName, sourceActor, targetActor);
}

FWasabiComplexStepState UAIWasabiEmotionEngine::GetWasabiComplexStepState() const
{
	return FWasabiComplexStepState(GetEngineCore()->GetWasabiEngineStepState(), GetEmotionState(), _timeElapsed);
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