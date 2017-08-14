// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionDummyActor.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISense_Sight.h"

AAIEmotionDummyActor::AAIEmotionDummyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Valency = EEmotionSimpleValency::Positive;
	bContinuous = false;
	Value = 0.5f;

	SightStimuliComponent = CreateDefaultSubobject<UAIEmotionSightStimuliComponent>(TEXT("AIEmotion Sight Stimuli Component"));
}

EEmotionSimpleValency AAIEmotionDummyActor::GetValency_Implementation()
{
	return Valency;
}
bool AAIEmotionDummyActor::IsContinuous_Implementation()
{
	return bContinuous;
}
float AAIEmotionDummyActor::GetValue_Implementation()
{
	return Value;
}