// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AIWasabiAppraisal.h"
#include "AIWasabiStructures.h"
#include "AIWasabiEmotionEngine.generated.h"

class UAIWasabiBaseEngineCore;
class UAIWasabiOriginalEngineCore;
class UAIWasabiImprovedEngineCore;

UCLASS(BlueprintType)
class PROJECT_API UAIWasabiEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Params")
		FAIWasabiAppraisal WasabiAppraisal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		EWasabiCoreType WasabiCoreType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		FWasabiCharacterTraits CharacterTraits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		bool bLogWasabiState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Params")
		TArray<FWasabiComplexStepState> WasabiStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
		TArray<FWasabiEmotion> KnownEmotions;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Params")
		UAIWasabiOriginalEngineCore* OriginalEngineCore;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Params")
		UAIWasabiImprovedEngineCore* ImprovedEngineCore;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float JoyDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float DistressDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float JoyDistressCoeficient;

	UAIWasabiBaseEngineCore* EngineCore;
	float _timeElapsed;

public:
	
	UAIWasabiEmotionEngine();
	
	virtual void InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
		virtual FAIEmotionState GetEmotionState() const override;

	FORCEINLINE UAIWasabiBaseEngineCore* GetEngineCore() const { return EngineCore; }

	UFUNCTION()
		virtual void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor) override; 

	UFUNCTION()
		FWasabiComplexStepState GetWasabiComplexStepState() const;

	FORCEINLINE TArray<FWasabiComplexStepState>* GetWasabiComplexStateStates() {return &WasabiStates; }

	FORCEINLINE EWasabiCoreType GetWasabiCoreType() const {return  WasabiCoreType;}
	FORCEINLINE void SetWasabiCoreType(EWasabiCoreType wasabiCoreType) { WasabiCoreType = wasabiCoreType; }

	FORCEINLINE bool GetLogWasabiState() const { return bLogWasabiState; }
	FORCEINLINE void SetLogWasabiState(bool logWasabiState) { bLogWasabiState = logWasabiState; }

	void AddEmotion(const FWasabiEmotion& newWasabiEmotion);

	FORCEINLINE FWasabiCharacterTraits GetCharacterTraits() const { return CharacterTraits; }
	FORCEINLINE void SetCharacterTraits(const FWasabiCharacterTraits& characterTraits) { CharacterTraits = characterTraits; }

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);
};