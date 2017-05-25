// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAIBaseAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionSystem.h"

#include "SandboxAIGameInstance.h"

#include "EmotionStimulus.h"
#include "SandboxAIStructures.h"

#include "DrawDebugHelpers.h"

ASandboxAIBaseAIController::ASandboxAIBaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	bAttachToPawn = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ASandboxAIBaseAIController::OnTargetPerceptionUpdatedCB);
	
	// sight sense
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sense Config Sight"));
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 30.0f;
	SenseConfig_Sight->SightRadius = 1000.0f;
	SenseConfig_Sight->LoseSightRadius = SenseConfig_Sight->SightRadius + 50.0f;
	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerception->ConfigureSense(*SenseConfig_Sight);

	// hearing sense
	SenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Sense Config Hearing"));
	SenseConfig_Hearing->HearingRange = 750.0f;
	SenseConfig_Hearing->LoSHearingRange = SenseConfig_Hearing->HearingRange + 50.0f;
	SenseConfig_Hearing->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	SenseConfig_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerception->ConfigureSense(*SenseConfig_Hearing);

	// damage sense
	SenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Sense Config Damage"));
	AIPerception->ConfigureSense(*SenseConfig_Damage);


	AIPerception->SetDominantSense(SenseConfig_Sight->GetSenseImplementation());
}

void ASandboxAIBaseAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	if (InPawn != nullptr && SenseConfig_Sight != nullptr)
	{
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SenseConfig_Sight->GetSenseImplementation(), InPawn);
	}
}

void ASandboxAIBaseAIController::UnPossess()
{
	Super::UnPossess();
}

FRotator ASandboxAIBaseAIController::GetControlRotation() const
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		return pawn->GetActorRotation();
	}
	else
	{
		return FRotator::ZeroRotator;
	}
}

void ASandboxAIBaseAIController::Tick(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	UWorld* world = GetWorld();
	if (world != nullptr)
	{
		UGameInstance* gameInstance = world->GetGameInstance();
		if (gameInstance != nullptr)
		{
			USandboxAIGameInstance* sandboxAIGameInstance = Cast<USandboxAIGameInstance>(gameInstance);
			if (sandboxAIGameInstance != nullptr)
			{
				if (sandboxAIGameInstance->ShouldShowGizmos())
				{
					DrawDebug(DeltaSeconds);
				}
			}
		}
	}
#endif
	const int32 stimulusCount = AffectingEmotionStimulusses.Num();
	for (int32 index = 0; index < stimulusCount; ++index)
	{
		IEmotionStimulus* emotionStimulus = AffectingEmotionStimulusses[index].EmotionStimulus;
		AActor* actor = AffectingEmotionStimulusses[index].Actor;
		if (emotionStimulus != nullptr)
		{
			// handle continuous elements
			const int32 elementCount = emotionStimulus->Execute_GetEmotionStimulusElementCount(actor);
			for (int32 elementIndex = 0; elementIndex < elementCount; ++elementIndex)
			{
				FEmotionStimulusElement emotionStimulusElement = emotionStimulus->Execute_GetEmotionStimulusElement(actor, elementIndex);
				if (emotionStimulusElement.bContinious)
				{
					emotionStimulusElement.Power = emotionStimulusElement.Power * DeltaSeconds;
					HandleEmotionStimulusElement(emotionStimulusElement);
				}
			}
		}
	}
}

void ASandboxAIBaseAIController::OnTargetPerceptionUpdatedCB(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor != nullptr)
	{

		UWorld* world = GetWorld();
		if (world != nullptr)
		{
			UGameInstance* gameInstance = world->GetGameInstance();
			if (gameInstance != nullptr)
			{
				USandboxAIGameInstance* sandboxAIGameInstance = Cast<USandboxAIGameInstance>(gameInstance);
				if (sandboxAIGameInstance != nullptr)
				{
					if (sandboxAIGameInstance->ShouldShowLogs())
					{
						FString message = FString::Printf(TEXT("%stected: %s"), Stimulus.WasSuccessfullySensed() ? TEXT("De") : TEXT("Unde"), *Actor->GetName());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, message);
					}
				}
			}
		}

		if (Stimulus.WasSuccessfullySensed())
		{
			IEmotionStimulus* emotionStimulus = Cast<IEmotionStimulus>(Actor);
			if (emotionStimulus != nullptr)
			{
				// handle one time elements
				//const int32 elementCount = emotionStimulus->GetEmotionStimulusElementCount();
				const int32 elementCount = emotionStimulus->Execute_GetEmotionStimulusElementCount(Actor);
				for (int32 elementIndex = 0; elementIndex < elementCount; ++elementIndex)
				{
					//const FEmotionStimulusElement emotionStimulusElement = emotionStimulus->GetEmotionStimulusElement(elementIndex);
					const FEmotionStimulusElement emotionStimulusElement = emotionStimulus->Execute_GetEmotionStimulusElement(Actor, elementIndex);
					if (!emotionStimulusElement.bContinious)
					{
						HandleEmotionStimulusElement(emotionStimulusElement);
					}
				}

				AffectingEmotionStimulusses.Add(FAffectingEmotionStimulus(Actor, emotionStimulus));
			}
		}
		else
		{
			const int32 count = AffectingEmotionStimulusses.Num();
			for (int32 index = 0; index < count; ++index)
			{
				if (AffectingEmotionStimulusses[index].Actor == Actor)
				{
					AffectingEmotionStimulusses.RemoveAt(index);
					break;
				}
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Sense Callback with nullptr"));
	}
	OnTargetPerceptionUpdatedCall(Actor, Stimulus);
}

void ASandboxAIBaseAIController::OnTargetPerceptionUpdatedCall_Implementation(AActor* Actor, FAIStimulus Stimulus)
{
	OnTargetPerceptionUpdatedInternal(Actor, Stimulus);
}

void ASandboxAIBaseAIController::OnTargetPerceptionUpdatedInternal(AActor* Actor, FAIStimulus Stimulus)
{

}

/** Used to handle incomming stimulusses */
UFUNCTION(BlueprintNativeEvent)
void ASandboxAIBaseAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement)
{
}


void ASandboxAIBaseAIController::DrawDebug(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	UWorld* world = GetWorld();
	APawn* pawn = GetPawn();
	if (world != nullptr && pawn != nullptr)
	{
		FTransform pawnTransform = pawn->GetTransform();
		FVector location = pawnTransform.GetLocation();
		
		if (SenseConfig_Sight != nullptr)
		{
			DrawDebugAltCone(world, pawnTransform.GetLocation(), FRotator( pawnTransform.GetRotation() ), SenseConfig_Sight->SightRadius, SenseConfig_Sight->PeripheralVisionAngleDegrees, SenseConfig_Sight->PeripheralVisionAngleDegrees, FColor::Green.WithAlpha(50));
			DrawDebugAltCone(world, pawnTransform.GetLocation(), FRotator( pawnTransform.GetRotation() ), SenseConfig_Sight->LoseSightRadius, SenseConfig_Sight->PeripheralVisionAngleDegrees, SenseConfig_Sight->PeripheralVisionAngleDegrees, FColor::Green.WithAlpha(15));
		}
		if (SenseConfig_Hearing != nullptr)
		{
			DrawDebugSphere(world, location, SenseConfig_Hearing->HearingRange, 16, FColor::Yellow.WithAlpha(50));
			DrawDebugSphere(world, location, SenseConfig_Hearing->LoSHearingRange, 16, FColor::Yellow.WithAlpha(15));
		}
	}
#endif
}