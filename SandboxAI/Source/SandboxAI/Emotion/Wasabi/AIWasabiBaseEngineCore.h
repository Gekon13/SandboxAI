// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AIWasabiStructures.h"
#include "AIWasabiBaseEngineCore.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SANDBOXAI_API UAIWasabiBaseEngineCore : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		FWasabiSpacePointPAD WasabiSpacePointPAD;
	
public:
	UAIWasabiBaseEngineCore();

	UFUNCTION(BlueprintCallable)
		virtual void Initialize();
	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value);
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintPure)
		FORCEINLINE FWasabiSpacePointPAD GetWasabiSpacePointPAD() const { return WasabiSpacePointPAD; }
};
