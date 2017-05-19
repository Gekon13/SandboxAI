// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAISplinePath.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

ASandboxAISplinePath::ASandboxAISplinePath()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	RootComponent = SceneComponent;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(SceneComponent);
}