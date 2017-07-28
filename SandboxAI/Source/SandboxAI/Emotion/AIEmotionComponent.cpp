// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEmotionComponent.h"


UAIEmotionComponent::UAIEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	EmotionKnowledge;
	EEmotionEngineModel::None;
}

void UAIEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAIEmotionComponent::TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);
}

