// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "Perception/AISense_Sight.h"
#include "AIEmotionSightStimuliComponent.h"


UAIEmotionSightStimuliComponent::UAIEmotionSightStimuliComponent(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	RegisterAsSourceForSenses.Add(UAISense_Sight::StaticClass());
	bAutoRegisterAsSource = true;
}

