// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "DummySplineAIController.h"

ADummySplineAIController::ADummySplineAIController() : Super()
{
	RunSpeed = 600.0f;
	SphereColor = FMath::Lerp<FLinearColor>(FLinearColor::Red, FLinearColor::Green, 0.5f);
}

void ADummySplineAIController::BeginPlay()
{
	Super::BeginPlay();
	LastRunSpeed = 0.0f;
	LastSphereColor = FLinearColor(0.0f, 0.0f, 0.0f);
}

void ADummySplineAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FollowSpeedMin = FollowSpeedMax = RunSpeed;
	if (RunSpeed != LastRunSpeed)
	{
		SetFollowSpeedCoefficient(0.0f);
		LastRunSpeed = RunSpeed;
	}
	if (SphereColor != LastSphereColor)
	{
		SetEmotionVisualColor(SphereColor);
		LastSphereColor = SphereColor;
	}
}


