// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIEmotionConstants.h"
#include "AIEmotionKnoledge.h"
#include "AIBaseEmotionEngine.h"
#include "AIEmotionComponent.generated.h"

class AIEmotionKnowledge;

/// Component responsible for simulating agents emotional state and taking actions respecting emotional state
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UAIEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BluepritReadWrite, Category = "Emotion | Parameters")
		AIEmotionKnowledge EmotionKnowledge;

	UPROPERTY(EditAnywhere, BluepritReadWrite, Category = "Emotion | Parameters")
		EEmotionEngineModel EmotionEngineModel;

protected:
	UPROPERTY(VisiableAnywhere, BlueprintReadOnly, Category = "Emotion | Parameters")
		FAIBaseEmotionEngine* EmotionEnginePtr;

public:	
	UAIEmotionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
	
	FORCEINLINE FAIBaseEmotionEngine* GetEmotionEngine() const { return EmotionEnginePtr; }
};
