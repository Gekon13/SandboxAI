// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionDummyPawn.h"


// Sets default values
AAIEmotionDummyPawn::AAIEmotionDummyPawn()
{
	Valency = EEmotionSimpleValency::Positive;
	bContinuous = false;
	Value = 0.3f;
}
