// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIBaseAIController.h"
#include "SandboxAISplineAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API ASandboxAISplineAIController : public ASandboxAIBaseAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spline follow")
		float FollowTolerance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spline follow")
		float FollowStepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline follow")
		float FollowSpeedMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline follow")
		float FollowSpeedMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline follow")
		float FollowSpeedCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline follow")
		float FollowSpeedCoefficient;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline follow")
		float CurrentSplineDistance;

	class ASandboxAISplineCharacter* SplineCharacter;
	class USplineComponent* SplineComponent;

	FVector DesiredLocation;
	FVector LastLocation;
	float SplineLength;
	float TotalDistanceCovered;

public:
	ASandboxAISplineAIController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	UFUNCTION(BlueprintCallable)
		void SetFollowSpeedCoefficient(float newFollowSpeedCoefficient); // USE THIS FOR SPEED

	UFUNCTION(BlueprintCallable)
		void SetEmotionVisualColor(FLinearColor newColor); // USE THIS FOR COLOR

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetFollowSpeedCoefficient(float newFollowSpeedCoefficient) { return FollowSpeedCoefficient; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetSplineLength() const { return SplineLength; }

protected:
	
	void GetNewDesiredLocation();

};
