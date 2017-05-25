// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FixedPath/SandboxAISplineAIController.h"
#include "DummySplineAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API ADummySplineAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()
	
protected:
	float LastRunSpeed;
	FLinearColor LastSphereColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy")
		float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy")
		FLinearColor SphereColor;
	
public:
	ADummySplineAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
};
