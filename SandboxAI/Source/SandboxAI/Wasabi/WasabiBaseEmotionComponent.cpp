// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiBaseEmotionComponent.h"
#include "Emotion/Wasabi/AIWasabiOriginalEngineCore.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"

// Sets default values for this component's properties
UWasabiBaseEmotionComponent::UWasabiBaseEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	WasabiEngineCore = CreateDefaultSubobject<UAIWasabiOriginalEngineCore>(TEXT("Wasabi Engine"));

	JoyDistance = 0.0f;
	DistressDistance = 0.0f;
}


// Called when the game starts
void UWasabiBaseEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	//if (WasabiEngineCore != nullptr)
	//{
	//	WasabiEngineCore->Initialize(CharacterTraits);
	//}
}

// Called every frame
void UWasabiBaseEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WasabiEngineCore != nullptr)
	{
		WasabiEngineCore->Tick(DeltaTime);

		FWasabiSpacePointPAD currentSpacePointPAD = WasabiEngineCore->GetWasabiSpacePointPAD();

		JoyDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::MockJoy);
		DistressDistance = FWasabiSpacePointPAD::Distance(currentSpacePointPAD, FWasabiSpacePointPADEmotion::MockDistress);
	}
}

void UWasabiBaseEmotionComponent::ReceiveImpulse(float value)
{
	if (WasabiEngineCore != nullptr)
	{
		WasabiEngineCore->Impulse(value);
	}
}