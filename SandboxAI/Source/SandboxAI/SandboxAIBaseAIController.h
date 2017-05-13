// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig.h"
#include "SandboxAIBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API ASandboxAIBaseAIController : public AAIController
{
	GENERATED_BODY()
	
protected: // make variables always protected

	/** AIPerception componnet */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception", meta = (BlueprintProtected = "true"))
		class UAIPerceptionComponent* AIPerception;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception", meta = (BlueprintProtected = "true"))
		class UAISenseConfig_Sight* SenseConfig_Sight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception", meta = (BlueprintProtected = "true"))
		class UAISenseConfig_Hearing* SenseConfig_Hearing;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Perception", meta = (BlueprintProtected = "true"))
		class UAISenseConfig_Damage* SenseConfig_Damage;

public: // public functions and callbacks
	
	ASandboxAIBaseAIController();
	
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;



protected: //internal functions and callback
	
	/** Called whenever perception componnet starts or stops to perceive stimulus source */
	UFUNCTION() //callback have to be marked UFUNCTION, otherwise they won't be called
		void OnTargetPerceptionUpdatedCB(AActor* Actor, FAIStimulus Stimulus);

	/** Override whenever needed */
	UFUNCTION(BlueprintNativeEvent)
		void OnTargetPerceptionUpdatedCall(AActor* Actor, FAIStimulus Stimulus); //in C++ override OnTargetPerceptionUpdated_Implementation, everything else should be setup

	/** Called whenever perception componnet starts or stops to perceive stimulus source */
	virtual void OnTargetPerceptionUpdatedInternal(AActor* Actor, FAIStimulus Stimulus);
};
