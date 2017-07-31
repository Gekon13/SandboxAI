// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionComponent.h"
#include "AIEmotionDummyPawn.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

UAIEmotionComponent::UAIEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FatimaEmotionEngine = CreateDefaultSubobject<UAIFatimaEmotionEngine>(TEXT("FATIMA"));
	PsiEmotionEngine = CreateDefaultSubobject<UAIPsiEmotionEngine>(TEXT("PSI"));
	SimplexEmotionEngine = CreateDefaultSubobject<UAISimplexEmotionEngine>(TEXT("SIMPLEX"));
	WasabiEmotionEngine = CreateDefaultSubobject<UAIWasabiEmotionEngine>(TEXT("WASABI"));

	EmotionEnginePtr = nullptr;
	EEmotionEngineModel::None;
}

void UAIEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (EmotionEngineModel != EEmotionEngineModel::None)
	{
		switch (EmotionEngineModel)
		{
		case EEmotionEngineModel::Fatima:
			{
				EmotionEnginePtr = FatimaEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Psi:
			{
				EmotionEnginePtr = PsiEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Simplex:
			{
				EmotionEnginePtr = SimplexEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Wasabi:
			{
				EmotionEnginePtr = WasabiEmotionEngine;
			}
			break;
		}

		if (GetEmotionEngine() != nullptr)
		{
			GetEmotionEngine()->InitializeEmotionEngine(&EmotionKnowledge);
			GetEmotionEngine()->OnPassDecision.BindSP(TSharedRef<UAIEmotionComponent>(this), &UAIEmotionComponent::ReceivePassedDecision);
		}
	}


	// Get owning actor
	AActor* owningActor = GetOwner();
	if (owningActor != nullptr)
	{
		AIController = Cast<AAIController>(owningActor);
		if (AIController != nullptr)
		{
			if (AIController->GetPerceptionComponent())
			{
				AIController->GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &UAIEmotionComponent::OnPerceptionUpdatedActor);
			}
		}
	}
}


void UAIEmotionComponent::TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);

	if (TickType != ELevelTick::LEVELTICK_PauseTick) // ensure we don't tick when game is paused
	{
		if (GetEmotionEngine() != nullptr)
		{
			int32 knownDummyPawnNumber = KnownDummyPawns.Num();
			for (int32 knownDummyPawnIndex = 0; knownDummyPawnIndex < knownDummyPawnNumber; ++knownDummyPawnIndex)
			{
				if (KnownDummyPawns[knownDummyPawnIndex]->bContinuous)
				{
					float continuousEmotionImpulseValue;
					switch (KnownDummyPawns[knownDummyPawnIndex]->Valency)
					{
					case EEmotionSimpleValency::Positive:
						continuousEmotionImpulseValue = 1.0f * KnownDummyPawns[knownDummyPawnIndex]->Value * DeltaSeconds;
						break;
					case EEmotionSimpleValency::Negative:
						continuousEmotionImpulseValue = -1.0f * KnownDummyPawns[knownDummyPawnIndex]->Value * DeltaSeconds;
						break;
					}
					GetEmotionEngine()->DirectValencedImpulse(continuousEmotionImpulseValue, true);
				}
			}
			GetEmotionEngine()->TickEmotionEngine(DeltaSeconds);
		}
	}
}

void UAIEmotionComponent::ReceivePassedDecision(const FEmotionDecisionInfo& decisionInfo)
{
	OnDecisionMade.Broadcast(decisionInfo);
}

void UAIEmotionComponent::OnPerceptionUpdatedActor(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor != nullptr)
	{
		AAIEmotionDummyPawn* dummyPawn = Cast<AAIEmotionDummyPawn>(Actor);
		if (dummyPawn != nullptr)
		{
			if (dummyPawn->bContinuous)
			{
				if (Stimulus.WasSuccessfullySensed())
				{
					KnownDummyPawns.Add(dummyPawn);
				}
				else
				{
					if (KnownDummyPawns.Contains(dummyPawn))
					{
						KnownDummyPawns.Remove(dummyPawn);
					}
				}
			}
			else
			{
				float emotionImpulseValue;
				switch (dummyPawn->Valency)
				{
				case EEmotionSimpleValency::Positive:
					emotionImpulseValue = 1.0f * dummyPawn->Value;
					break;
				case EEmotionSimpleValency::Negative:
					emotionImpulseValue = -1.0f * dummyPawn->Value;
					break;
				}
				GetEmotionEngine()->DirectValencedImpulse(emotionImpulseValue, false);
			}
		}
	}
}