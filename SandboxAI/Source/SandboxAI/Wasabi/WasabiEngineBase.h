// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Wasabi/WasabiStructures.h"
#include "WasabiEngineBase.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API UWasabiEngineBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FWasabiSpacePointPAD WasabiSpacePointPAD;
	
public:
	UWasabiEngineBase();
	UWasabiEngineBase(const FWasabiSpacePointPAD& startSpacePointPAD);

	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value);
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds);
};
