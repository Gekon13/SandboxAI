// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SandboxAISplinePath.generated.h"

UCLASS()
class SANDBOXAI_API ASandboxAISplinePath : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BlueprintPrivateAccess = "true"))
		class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BlueprintProtected = "true"))
		class USplineComponent* SplineComponent;

public:	
	ASandboxAISplinePath();

	UFUNCTION(BlueprintPure)
		FORCEINLINE class USplineComponent* GetSplineComponent() const { return SplineComponent; }
};
