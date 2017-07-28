// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIEmotionConstants.h"
#include "AIEmotionKnowledge.h"
#include "AIBaseEmotionEngine.h"

#include "Fatima/AIFatimaEmotionEngine.h"
#include "Psi/AIPsiEmotionEngine.h"
#include "Simplex/AISimplexEmotionEngine.h"
#include "Wasabi/AIWasabiEmotionEngine.h"

#include "AIEmotionComponent.generated.h"

/// Component responsible for simulating agents emotional state and taking actions respecting emotional state
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UAIEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		FAIEmotionKnowledge EmotionKnowledge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		EEmotionEngineModel EmotionEngineModel;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		FAIFatimaEmotionEngine FatimaEmotionEngine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		FAIPsiEmotionEngine PsiEmotionEngine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		FAISimplexEmotionEngine SimplexEmotionEngine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		FAIWasabiEmotionEngine WasabiEmotionEngine;

	FAIBaseEmotionEngine* EmotionEnginePtr;

public:	
	UAIEmotionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
	
	FORCEINLINE FAIBaseEmotionEngine* GetEmotionEngine() const { return EmotionEnginePtr; }
};
