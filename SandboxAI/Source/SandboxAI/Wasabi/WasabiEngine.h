// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wasabi/WasabiEngineBase.h"
#include "Wasabi/WasabiStructures.h"
#include "WasabiEngine.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class SANDBOXAI_API UWasabiEngine : public UWasabiEngineBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		FWasabiSpacePointVMB WasabiSpacePointVMB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		float ValenceVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		float MoodVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float ValenceTension; // default from wasabi is 69
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float MoodTension; // default from wasabi is 10
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Mass; // default from wasabi is 5000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Temperament; // default from wasabi is 500 // in wasabi engine it's called Slope
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float ValenceBoredoomRegion; // default from wasabi is 5
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float MoodBoredoomRegion; // default from wasabi is 5
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float BoredoomPerSecond; // default from wasabi is 50
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Prevalence; // default from wasabi is 30

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float OverrideDominance; // for now

	/** Whether to use implementation or theory from papers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		bool bUseTheoryMoodAffecting; // default from wasabi is 30
	
	/** Whether to affect mood from Valence */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		bool bValenceAffectMood;

	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|params")
		bool bPendingImpulse;
	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|params")
		float PendingImpulseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|params")
		FWasabiEngineStepState LastEngineStepState;

	int32 _stepCounter;

public:
	UWasabiEngine();
	
	UFUNCTION(BlueprintCallable)
		virtual void Initialize() override;
	UFUNCTION(BlueprintCallable)
		virtual void Impulse(float value) override;
	UFUNCTION(BlueprintCallable)
		virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
		FWasabiEngineStepState GetEngineStateState();

protected:
	/** Call this to apply impulse directly to VMB space */
	void InternalImpulse(float value);
	void MapVMBToPAD();
};
