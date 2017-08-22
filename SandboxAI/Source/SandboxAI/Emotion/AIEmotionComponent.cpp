// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionComponent.h"
#include "Dummies/AIEmotionDummyInterface.h"
#include "AIEmotionVisibleInterface.h"

#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

UAIEmotionComponent::UAIEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	EmotionKnowledge = CreateDefaultSubobject<UAIEmotionKnowledge>(TEXT("Knowledge"));

	FatimaEmotionEngine = CreateDefaultSubobject<UAIFatimaEmotionEngine>(TEXT("FATIMA"));
	PsiEmotionEngine = CreateDefaultSubobject<UAIPsiEmotionEngine>(TEXT("PSI"));
	SimplexEmotionEngine = CreateDefaultSubobject<UAISimplexEmotionEngine>(TEXT("SIMPLEX"));
	WasabiEmotionEngine = CreateDefaultSubobject<UAIWasabiEmotionEngine>(TEXT("WASABI"));

	EmotionEnginePtr = nullptr;
	EmotionEngineModel = EEmotionEngineModel::None;
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

		if (GetEmotionEngine() != nullptr && EmotionKnowledge != nullptr)
		{
			GetEmotionEngine()->InitializeEmotionEngine(EmotionKnowledge);
			GetEmotionEngine()->OnPassDecision.BindUObject(this, &UAIEmotionComponent::ReceivePassedDecision);
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

			ControlledPawn = AIController->GetPawn();
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
			int32 knownDummyNumber = KnownEmotionDummies.Num();
			for (int32 knownDummyIndex = 0; knownDummyIndex < knownDummyNumber; ++knownDummyIndex)
			{
				IAIEmotionDummyInterface* emotionDummy = KnownEmotionDummies[knownDummyIndex];
				if (emotionDummy->Execute_IsContinuous(Cast<UObject>(emotionDummy)))
				{
					float continuousEmotionImpulseValue = 0.0f;
					switch (emotionDummy->Execute_GetValency(Cast<UObject>(emotionDummy)))
					{
					case EEmotionSimpleValency::Positive:
						continuousEmotionImpulseValue = 1.0f * emotionDummy->Execute_GetValue(Cast<UObject>(emotionDummy)) * DeltaSeconds;
						break;
					case EEmotionSimpleValency::Negative:
						continuousEmotionImpulseValue = -1.0f * emotionDummy->Execute_GetValue(Cast<UObject>(emotionDummy)) * DeltaSeconds;
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
	//UE_LOG(LogTemp, Log, TEXT("[%s] See: %s"), *GetName(), *Actor->GetName());
	if (GetEmotionEngine() != nullptr && Actor != nullptr)
	{
		IAIEmotionDummyInterface* emotionDummy = Cast<IAIEmotionDummyInterface>(Actor);
		if (emotionDummy != nullptr)
		{
			if (emotionDummy->Execute_IsContinuous(Cast<UObject>(emotionDummy)))
			{
				if (Stimulus.WasSuccessfullySensed())
				{
					KnownEmotionDummies.Add(emotionDummy);
				}
				else
				{
					if (KnownEmotionDummies.Contains(emotionDummy))
					{
						KnownEmotionDummies.Remove(emotionDummy);
					}
				}
			}
			else
			{
				float emotionImpulseValue = 0.0f;
				switch (emotionDummy->Execute_GetValency(Cast<UObject>(emotionDummy)))
				{
				case EEmotionSimpleValency::Positive:
					emotionImpulseValue = 1.0f * emotionDummy->Execute_GetValue(Cast<UObject>(emotionDummy));
					break;
				case EEmotionSimpleValency::Negative:
					emotionImpulseValue = -1.0f * emotionDummy->Execute_GetValue(Cast<UObject>(emotionDummy));
					break;
				}
				GetEmotionEngine()->DirectValencedImpulse(emotionImpulseValue, false);
			}
		}

		if (Stimulus.Type == UAISense_Sight::GetSenseID(UAISense_Sight::StaticClass()))
		{
			IAIEmotionVisibleInterface* emotionVisible = Cast<IAIEmotionVisibleInterface>(Actor);
			if (emotionVisible != nullptr)
			{
				if (Stimulus.WasSuccessfullySensed())
				{
					emotionVisible->OnEmotionActionPerformed.AddDynamic(GetEmotionEngine(), &UAIBaseEmotionEngine::HandleEmotionActionPerformed);
					emotionVisible->RequestSeeAction(ControlledPawn);
				}
				else
				{
					emotionVisible->RequestUnSeeAction(ControlledPawn);
					emotionVisible->OnEmotionActionPerformed.RemoveDynamic(GetEmotionEngine(), &UAIBaseEmotionEngine::HandleEmotionActionPerformed);
				}
			}
		}

		if (GetEmotionEngine()->DoesImplementCustomCognition())
		{
			GetEmotionEngine()->OnTargetPerceptionUpdated(Actor, Stimulus);
		}
	}
}