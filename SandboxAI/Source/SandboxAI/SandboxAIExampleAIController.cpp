// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAIExampleAIController.h"

ASandboxAIExampleAIController::ASandboxAIExampleAIController()
{
	PatrolRadius = 300.0f;
	PatrolToleranceDistance = 75.0f;
	PatrolCenter = FVector::ZeroVector;
	PatrolTimer = 0.0f;
	PatrolTimeMultiplier = 1.0f;
}

void ASandboxAIExampleAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	PossesedCharacter = Cast<ACharacter>(InPawn);
	if (PossesedCharacter != nullptr)
	{
		PatrolCenter = PossesedCharacter->GetActorLocation();
		PatrolTimer = 0.0f;
	}
}

void ASandboxAIExampleAIController::UnPossess()
{
	Super::UnPossess();
	PossesedCharacter = nullptr;
}

void ASandboxAIExampleAIController::Tick(float DeltaSeconds)
{
	if (PossesedCharacter != nullptr)
	{
		PatrolTimer += DeltaSeconds * PatrolTimeMultiplier;

		FVector actorLocation = PossesedCharacter->GetActorLocation();

		FVector desiredLocation = PatrolCenter;
		desiredLocation.X += FMath::Sin(PatrolTimer) * PatrolRadius;
		desiredLocation.Y += FMath::Cos(PatrolTimer) * PatrolRadius;
		desiredLocation.Z = actorLocation.Z;

		FVector boom = desiredLocation - actorLocation;
		FVector direction = boom;
		direction.Normalize();
		float distance = boom.Size();

		float value = FMath::Clamp<float>(distance / PatrolToleranceDistance, 0.0f, 1.0f);

		PossesedCharacter->AddMovementInput(direction, value);
		GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Yellow, FString::Printf(TEXT("input: (%f;%f;%f), value: %f"), direction.X, direction.Y, direction.Z, value));
		//SetFocalPoint(desiredLocation);
	}
}


