// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAISplineCharacter.h"
#include "SandboxAISplineAIController.h"
#include "Components/SplineComponent.h"
#include "SandboxAISplinePath.h"

#include "DrawDebugHelpers.h"

ASandboxAISplineCharacter::ASandboxAISplineCharacter()
{
	AIControllerClass = ASandboxAISplineAIController::StaticClass();

	EmotionVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Emotion Visual"));
	EmotionVisualMesh->SetupAttachment(RootComponent);
	EmotionVisualMesh->SetRelativeLocation(FVector::UpVector * 200.0f);

	ColorParameterName = FName(TEXT("EmotionColor"));

	EmotionVisualMaterialInstance = nullptr;
}

void ASandboxAISplineCharacter::OnConstruction(const FTransform& Transform)
{
	if (SplinePath != nullptr && SplinePath->GetSplineComponent() != nullptr && SplinePath->GetSplineComponent()->GetNumberOfSplinePoints() > 0)
	{
		FVector location = SplinePath->GetSplineComponent()->GetWorldLocationAtSplinePoint(0);
	 	FRotator rotation = SplinePath->GetSplineComponent()->GetRotationAtSplinePoint(0, ESplineCoordinateSpace::World);

		SetActorLocation(location);
		SetActorRotation(rotation);
	}
}

USplineComponent* ASandboxAISplineCharacter::GetSplineComponent() const
{
	return SplinePath != nullptr ? SplinePath->GetSplineComponent() : nullptr;
}

void ASandboxAISplineCharacter::SetEmotionVisualColor(FLinearColor newColor)
{
	if (EmotionVisualMaterialInstance == nullptr)
	{
		UMaterialInterface* material = EmotionVisualMesh->GetMaterial(0);
		EmotionVisualMaterialInstance = EmotionVisualMesh->CreateDynamicMaterialInstance(0, material);
	}
	if (EmotionVisualMaterialInstance != nullptr)
	{
		EmotionVisualMaterialInstance->SetVectorParameterValue(ColorParameterName, newColor);
	}
}