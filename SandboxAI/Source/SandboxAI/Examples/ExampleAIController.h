// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SandboxAIBaseAIController.h"
#include "ExampleAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API AExampleAIController : public ASandboxAIBaseAIController
{
	GENERATED_BODY()
	
protected:
	/** Patrol radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProtected = "true"))
		float PatrolRadius;

	/** Distance from desired location percived as on point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProtected = "true"))
		float PatrolToleranceDistance;

	/** Patrol center of circle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProtected = "true"))
		FVector PatrolCenter;

	/** Patrol circle timer */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProtected = "true"))
		float PatrolTimer;

	/** Patrol circle time multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProtected = "true"))
		float PatrolTimeMultiplier;

	/** Cached ptr */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (BlueprintProtected = "true"))
		ACharacter* PossesedCharacter;

	/** Valence */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (BlueprintProtected = "true"))
		float Valence;

public:
	AExampleAIController();

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement) override;
};
