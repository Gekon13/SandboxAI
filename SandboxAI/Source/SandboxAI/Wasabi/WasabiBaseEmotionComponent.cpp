// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiBaseEmotionComponent.h"
#include "Wasabi/WasabiEngine.h"
#include "Wasabi/WasabiStructures.h"

// Sets default values for this component's properties
UWasabiBaseEmotionComponent::UWasabiBaseEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	WasabiEngine = CreateDefaultSubobject<UWasabiEngine>(TEXT("Wasabi Engine"));

	JoyDistance = 0.0f;
	DistressDistance = 0.0f;
}


// Called when the game starts
void UWasabiBaseEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (WasabiEngine != nullptr)
	{
		WasabiEngine->Initialize();
	}
}

// Called every frame
void UWasabiBaseEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WasabiEngine != nullptr)
	{
		WasabiEngine->Tick(DeltaTime);

		FWasabiSpacePointPAD currentSpacePointPAD = WasabiEngine->GetWasabiSpacePointPAD();

		JoyDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::Joy);
		DistressDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::Distress);
	}
}

void UWasabiBaseEmotionComponent::ReceiveImpulse(float value)
{
	if (WasabiEngine != nullptr)
	{
		WasabiEngine->Impulse(value);
	}
}