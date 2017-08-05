// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionDummyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAIEmotionDummyPawn::AAIEmotionDummyPawn()
{
	Valency = EEmotionSimpleValency::Positive;
	bContinuous = false;
	Value = 0.5f;
}

EEmotionSimpleValency AAIEmotionDummyPawn::GetValency_Implementation()
{
	return Valency;
}
bool AAIEmotionDummyPawn::IsContinuous_Implementation()
{
	return bContinuous;
}
float AAIEmotionDummyPawn::GetValue_Implementation()
{
	return Value;
}