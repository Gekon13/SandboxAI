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

	//UAISenseConfig* config;
	//UAISenseConfig_Sight::
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerception Stimuli source"));
	
	//StimuliSourceComponent->bAutoRegisterAsSource = true;
	//UAISense_Sight sightSense;
	//sightSense.
	StimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
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