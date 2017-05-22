// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wasabi/WasabiEngineBase.h"
#include "Wasabi/WasabiStructures.h"
#include "WasabiEngine.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API UWasabiEngine : public UWasabiEngineBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FWasabiSpacePointVMB WasabiSpacePointVMB;

public:
	UWasabiEngine();
	UWasabiEngine(const FWasabiSpacePointPAD& startSpacePointPAD);
	
	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value) override;
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds) override;
};
