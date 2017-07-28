// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WasabiStructures.h"
#include "WasabiEngineBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SANDBOXAI_API UWasabiEngineBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		FWasabiSpacePointPAD WasabiSpacePointPAD;
	
public:
	UWasabiEngineBase();

	UFUNCTION(BlueprintCallable)
		virtual void Initialize();
	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value);
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintPure)
		FORCEINLINE FWasabiSpacePointPAD GetWasabiSpacePointPAD() { return WasabiSpacePointPAD; }
};
