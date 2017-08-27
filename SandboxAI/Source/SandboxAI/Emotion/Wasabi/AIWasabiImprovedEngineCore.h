// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIWasabiBaseEngineCore.h"
#include "AIWasabiStructures.h"
#include "AIWasabiImprovedEngineCore.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class PROJECT_API UAIWasabiImprovedEngineCore : public UAIWasabiBaseEngineCore
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		FWasabiSpacePointVMB WasabiSpacePointVMB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		float ValenceVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		float MoodVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|State")
		float DisequilibriumVelocity;

	/** default from wasabi is 69 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float ValenceTension; // default from wasabi is 69
	/** default from wasabi is 10 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float MoodTension; // default from wasabi is 10
	/** default from wasabi is 5000 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Mass; // default from wasabi is 5000
	/** default from wasabi is 500 | in wasabi engine it's called Slope */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Slope; // default from wasabi is 500 // in wasabi engine it's called Slope
	/** default from wasabi is 5 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float ValenceBoredomRegion; // default from wasabi is 5
	/** default from wasabi is 5 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float MoodBoredomRegion; // default from wasabi is 5
	/** default from wasabi is 50 | My default is 10*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float BoredomPerSecond; // default from wasabi is 50
	/** default from wasabi is 30 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Prevalence; // default from wasabi is 30


	/** rate defining how much Disequilibrium should grow from equasion */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float Disequilibrium;
	/** how fast disequilibrium does decay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float BoredomTension;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		float OverrideDominance; // for now

	/** Whether to use implementation or theory from papers */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		bool bUseTheoryMoodAffecting; // default from wasabi is 30
	
	/** Whether to affect mood from Valence */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi|Params")
		bool bValenceAffectMood;

	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|Params")
		bool bPendingImpulse;
	/** Whether there is a valenced impulse pending */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|Params")
		float PendingImpulseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wasabi|Params")
		FWasabiEngineStepState LastEngineStepState;

	int32 _stepCounter;

	

public:
	UAIWasabiImprovedEngineCore();
	
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
