// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AIWasabiStructures.h"
#include "../AIEmotionState.h"
#include "AIWasabiBaseEngineCore.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_API UAIWasabiBaseEngineCore : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		FWasabiSpacePointPAD WasabiSpacePointPAD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi | Params")
		TArray<FWasabiEmotion> KnownEmotions;

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

	UFUNCTION(BlueprintCallable)
		void AddEmotionToEngine(const FWasabiEmotion& wasabiEmotion);

	UFUNCTION(BlueprintCallable)
		virtual FAIEmotionState GetEmotionState(bool onlyActiveEmotions = true) const;
};
