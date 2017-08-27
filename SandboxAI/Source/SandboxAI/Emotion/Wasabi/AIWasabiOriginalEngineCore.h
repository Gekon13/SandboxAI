// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIWasabiBaseEngineCore.h"
#include "AIWasabiStructures.h"
#include "AIWasabiOriginalEngineCore.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class PROJECT_API UAIWasabiOriginalEngineCore : public UAIWasabiBaseEngineCore
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		FWasabiSpacePointVMB WasabiSpacePointVMB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float ValenceVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		float MoodVelocity;

	/** default from wasabi is 69 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float ValenceTension; // default from wasabi is 69
	/** default from wasabi is 10 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float MoodTension; // default from wasabi is 10
	/** default from wasabi is 5000 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float Mass; // default from wasabi is 5000
	/** default from wasabi is 500 | in wasabi engine it's called Slope */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float Slope; // default from wasabi is 500 // in wasabi engine it's called Slope
	/** default from wasabi is 5 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float ValenceBoredomRegion; // default from wasabi is 5
	/** default from wasabi is 5 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float MoodBoredomRegion; // default from wasabi is 5
	/** default from wasabi is 50 | My default is 10*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float BoredomPerSecond; // default from wasabi is 50
	/** default from wasabi is 30 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		float Prevalence; // default from wasabi is 30

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		float OverrideDominance; // for now

	/** Whether to use implementation or theory from papers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		bool bUseTheoryMoodAffecting;

	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Params")
		bool bPendingImpulse;
	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Params")
		float PendingImpulseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Params")
		FWasabiEngineStepState LastEngineStepState;

	int32 _stepCounter;

public:
	UAIWasabiOriginalEngineCore();
	
	UFUNCTION(BlueprintCallable)
		virtual void Initialize(const FWasabiCharacterTraits& characterTraits) override;
	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value) override;
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE FWasabiEngineStepState GetEngineStepState() { return LastEngineStepState;	}



protected:
	/** Call this to apply impulse directly to VMB space */
	void InternalImpulse(float value);
	void MapVMBToPAD();

	virtual void MapCharacterTraitsToParams(const FWasabiCharacterTraits& characterTraits) override;
};
