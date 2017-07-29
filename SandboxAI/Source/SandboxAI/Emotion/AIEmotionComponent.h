// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIEmotionConstants.h"
#include "AIEmotionKnowledge.h"
#include "AIBaseEmotionEngine.h"
#include "AIEmotionDecisionInfo.h"

#include "Fatima/AIFatimaEmotionEngine.h"
#include "Psi/AIPsiEmotionEngine.h"
#include "Simplex/AISimplexEmotionEngine.h"
#include "Wasabi/AIWasabiEmotionEngine.h"

#include "AIEmotionComponent.generated.h"

class UAIEmotionComponent;

DECLARE_EVENT_OneParam(UAIEmotionComponent, FDecisionMade, const FEmotionDecisionInfo&)

/// Component responsible for simulating agents emotional state and taking actions respecting emotional state
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UAIEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Knowledge")
		FAIEmotionKnowledge EmotionKnowledge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		EEmotionEngineModel EmotionEngineModel;

	FDecisionMade OnDecisionMade;

protected:
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Emotion | Fatima")
		UAIFatimaEmotionEngine* FatimaEmotionEngine;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Emotion | Psi")
		UAIPsiEmotionEngine* PsiEmotionEngine;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Emotion | Simplex")
		UAISimplexEmotionEngine* SimplexEmotionEngine;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Emotion | Wasabi")
		UAIWasabiEmotionEngine* WasabiEmotionEngine;

	UAIBaseEmotionEngine* EmotionEnginePtr;

public:	
	UAIEmotionComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
	
	FORCEINLINE UAIBaseEmotionEngine* GetEmotionEngine() const { return EmotionEnginePtr; }

protected:

	void ReceivePassedDecision(const FEmotionDecisionInfo& decisionInfo);
};
