// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SandboxAIExampleAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API ASandboxAIExampleAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	/** Patrol radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProteted = "true"))
		float PatrolRadius;

	/** Distance from desired location percived as on point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProteted = "true"))
		float PatrolToleranceDistance;

	/** Patrol center of circle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProteted = "true"))
		FVector PatrolCenter;

	/** Patrol circle timer */
	UPROPERTY(BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProteted = "true"))
		float PatrolTimer;

	/** Patrol circle time multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (BlueprintProteted = "true"))
		float PatrolTimeMultiplier;

	/** Cached ptr */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (BlueprintProtected = "true"))
		ACharacter* PossesedCharacter;

public:
	ASandboxAIExampleAIController();

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	virtual void Tick(float DeltaSeconds) override;
	
};
