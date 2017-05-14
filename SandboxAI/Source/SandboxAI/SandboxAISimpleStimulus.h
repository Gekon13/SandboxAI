// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EmotionStimulus.h"
#include "SandboxAIStructures.h"
#include "SandboxAISimpleStimulus.generated.h"

UCLASS(BlueprintType)
class SANDBOXAI_API ASandboxAISimpleStimulus : public AActor, public IEmotionStimulus
{
	GENERATED_BODY()
protected:

	/** Whether this should affect in one time action or inevery tick */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotions", meta = (BlueprintProtected = "true"))
		TArray<FEmotionStimulusElement> EmotionStimulusElements;

public:	
	ASandboxAISimpleStimulus();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual int32 GetEmotionStimulusElementCount_Implementation() const override;

	virtual FEmotionStimulusElement GetEmotionStimulusElement_Implementation(const int32& index) const override;
};
