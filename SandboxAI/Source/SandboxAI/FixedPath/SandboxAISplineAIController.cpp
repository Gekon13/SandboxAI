// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "FixedPath/SandboxAISplineAIController.h"
#include "FixedPath/SandboxAISplineCharacter.h"
#include "Components/SplineComponent.h"

ASandboxAISplineAIController::ASandboxAISplineAIController()
{
	FollowTolerance = 50.0f;
	FollowStepDistance = 10.0f;
	FollowSpeedMin = 300.0f;
	FollowSpeedMax = 900.0f;
	FollowSpeedCurrent = 600.0f;
	FollowSpeedCoefficient = 0.5f;
	CurrentSplineDistance = 0.0f;
	TotalDistanceCovered = 0.0f;
}

void ASandboxAISplineAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	if (InPawn != nullptr)
	{
		SplineCharacter = Cast<ASandboxAISplineCharacter>(InPawn);
		if (SplineCharacter != nullptr)
		{
			UCharacterMovementComponent* movementComponent = SplineCharacter->GetCharacterMovement();
			if (movementComponent != nullptr)
			{
				movementComponent->MaxWalkSpeed = FollowSpeedCurrent;

				SplineComponent = SplineCharacter->GetSplineComponent();
				if (SplineComponent != nullptr)
				{
					SplineLength = SplineComponent->GetSplineLength();
					
					LastLocation = InPawn->GetActorLocation();
					LastLocation.Z = 0.0f;
				}
			}
		}
	}
}
void ASandboxAISplineAIController::UnPossess()
{
	Super::UnPossess();
}

void ASandboxAISplineAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (SplineComponent != nullptr)
	{
		if (CurrentSplineDistance < SplineLength || SplineComponent->IsClosedLoop())
		{
			FVector location = GetPawn()->GetActorLocation();
			location.Z = 0.0f;

			float distanceDone = FVector::Distance(location, LastLocation);
			CurrentSplineDistance += distanceDone;
			TotalDistanceCovered += distanceDone;

			GetNewDesiredLocation();
			
			FVector direction = DesiredLocation - location;
			direction.Normalize();

			GetPawn()->AddMovementInput(direction);

			LastLocation = location;
		}
	}

#if ENABLE_DRAW_DEBUG

	UWorld* world = GetWorld();
	APawn* pawn = GetPawn();
	if (world != nullptr && pawn != nullptr)
	{
		DrawDebugLine(world, pawn->GetActorLocation(), DesiredLocation, FColor::Red);
	}

#endif
}

void ASandboxAISplineAIController::SetFollowSpeedCoefficient(float newFollowSpeedCoefficient)
{
	FollowSpeedCoefficient = newFollowSpeedCoefficient;
	FollowSpeedCurrent = FMath::Lerp<float>(FollowSpeedMin, FollowSpeedMax, FollowSpeedCoefficient);
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		ASandboxAISplineCharacter* character = Cast<ASandboxAISplineCharacter>(pawn);
		if (character != nullptr)
		{
			UCharacterMovementComponent* movementComponent = character->GetCharacterMovement();
			movementComponent->MaxWalkSpeed = FollowSpeedCurrent;
		}
	}
}

void ASandboxAISplineAIController::GetNewDesiredLocation()
{
	if (SplineComponent != nullptr)
	{
		
		if (SplineComponent->IsClosedLoop() && CurrentSplineDistance > SplineLength)
		{
			CurrentSplineDistance -= SplineLength;
		}
		if (CurrentSplineDistance < SplineLength)
		{
			DesiredLocation = SplineComponent->GetWorldLocationAtDistanceAlongSpline(CurrentSplineDistance + FollowStepDistance);
			DesiredLocation.Z = 0.0f;
		}
	}
}

void ASandboxAISplineAIController::SetEmotionVisualColor(FLinearColor newColor)
{
	if (SplineCharacter != nullptr)
	{
		SplineCharacter->SetEmotionVisualColor(newColor);
	}
}