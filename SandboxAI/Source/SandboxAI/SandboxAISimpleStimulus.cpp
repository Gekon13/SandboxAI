// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SandboxAISimpleStimulus.h"


// Sets default values
ASandboxAISimpleStimulus::ASandboxAISimpleStimulus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASandboxAISimpleStimulus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandboxAISimpleStimulus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ASandboxAISimpleStimulus::GetEmotionStimulusElementCount_Implementation() const
{
	return EmotionStimulusElements.Num();
}

FEmotionStimulusElement ASandboxAISimpleStimulus::GetEmotionStimulusElement_Implementation(const int32& index) const
{
	return EmotionStimulusElements[index];
}