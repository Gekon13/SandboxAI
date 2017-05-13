// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAIBaseAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionSystem.h"

ASandboxAIBaseAIController::ASandboxAIBaseAIController()
{
	bAttachToPawn = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ASandboxAIBaseAIController::OnTargetPerceptionUpdatedCB);
	
	// sight sense
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sense Config Sight"));
	SenseConfig_Sight->PeripheralVisionAngleDegrees = 45.0f;
	SenseConfig_Sight->SightRadius = 3000.0f;
	SenseConfig_Sight->LoseSightRadius = SenseConfig_Sight->SightRadius + 50.0f;
	SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AIPerception->ConfigureSense(*SenseConfig_Sight);

	// hearing sense
	SenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Sense Config Hearing"));
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
	if (InPawn != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("register"));
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SenseConfig_Sight->GetSenseImplementation(), InPawn);
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("No pawn"));
	}
}

void ASandboxAIBaseAIController::UnPossess()
{
	Super::UnPossess();
}

void ASandboxAIBaseAIController::OnTargetPerceptionUpdatedCB(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor != nullptr)
	{
		FString message = FString::Printf(TEXT("%stected: %s"), Stimulus.WasSuccessfullySensed() ? TEXT("De") : TEXT("Unde"), *Actor->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, message);
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