// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Common/AIEmotionConstants.h"
#include "Common/AIEmotionKnowledge.h"
#include "Common/AIEmotionDecisionInfo.h"
#include "AIBaseEmotionEngine.h"

#include "Fatima/AIFatimaEmotionEngine.h"
#include "Psi/AIPsiEmotionEngine.h"
#include "Simplex/AISimplexEmotionEngine.h"
#include "Wasabi/AIWasabiEmotionEngine.h"

#include "AIEmotionComponent.generated.h"

class UAIEmotionComponent;
class APawn;
class AAIController;
class AAIEmotionDummyPawn;
class IAIEmotionDummyInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDecisionMade, const FEmotionDecisionInfo&, decisionInfo);

/// Component responsible for simulating agents emotional state and taking actions respecting emotional state
UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), HideCategories = (Activation, Variable, Collision, Cooking), meta = (BlueprintSpawnableComponent))
class PROJECT_API UAIEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		EEmotionEngineModel EmotionEngineModel;
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Emotion | Parameters")
		UAIEmotionKnowledge* EmotionKnowledge;

	UPROPERTY(BlueprintAssignable, Category = "Emotion")
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
	APawn* ControlledPawn;
	AAIController* AIController;
	TArray<IAIEmotionDummyInterface*> KnownEmotionDummies;

public:	
	UAIEmotionComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
	
	FORCEINLINE UAIBaseEmotionEngine* GetEmotionEngine() const { return EmotionEnginePtr; }

	FORCEINLINE UAIFatimaEmotionEngine* GetFatimaEmotionEngine() const {return FatimaEmotionEngine;}
	FORCEINLINE UAIPsiEmotionEngine* GetPsiEmotionEngine() const {return PsiEmotionEngine;}
	FORCEINLINE UAISimplexEmotionEngine* GetSimplexEmotionEngine() const { return SimplexEmotionEngine; }
	FORCEINLINE UAIWasabiEmotionEngine* GetWasabiEmotionEngine() const { return WasabiEmotionEngine; }

protected:

	void ReceivePassedDecision(const FEmotionDecisionInfo& decisionInfo);

	UFUNCTION()
	void OnPerceptionUpdatedActor(AActor* Actor, FAIStimulus Stimulus);
};
