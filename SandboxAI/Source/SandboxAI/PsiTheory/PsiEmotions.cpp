// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "PsiEmotions.h"


// Sets default values for this component's properties
UPsiEmotions::UPsiEmotions()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Emotions.Add(FPsiEmotion());
	// ...
}


// Called when the game starts
void UPsiEmotions::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPsiEmotions::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPsiEmotions::ProcessEmotionStimulusElement(const FEmotionStimulusElement & EmotionStimulusElement)
{
	switch (EmotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		Emotions[0].Value = FMath::Clamp(Emotions[0].Value - (EmotionStimulusElement.Power / 100.f), -1.0f, 1.0f) * 0.8f;
		break;
	case EEmotionStimulusElementType::ENegative:
		Emotions[0].Value = FMath::Clamp(Emotions[0].Value + (EmotionStimulusElement.Power / 100.f), -1.0f, 1.0f) * 0.8f;
		break;
	}
}

