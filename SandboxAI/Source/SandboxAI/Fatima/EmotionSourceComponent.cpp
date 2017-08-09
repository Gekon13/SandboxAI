// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "EmotionSourceComponent.h"


UEmotionSourceComponent::UEmotionSourceComponent() {
	PrimaryComponentTick.bCanEverTick = true;

	bContinuous = false;
}

void UEmotionSourceComponent::BeginPlay() {
	Super::BeginPlay();

	// ...

}

void UEmotionSourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
