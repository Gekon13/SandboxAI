// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "Emotion/Wasabi/AIWasabiAppraisal.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"
#include "AIWasabiEmotionEngine.generated.h"

class UAIWasabiBaseEngineCore;
class UAIWasabiOriginalEngineCore;
class UAIWasabiImprovedEngineCore;

UCLASS(BlueprintType)
class PROJECT_API UAIWasabiEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "")
		FAIWasabiAppraisal WasabiAppraisal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		EWasabiCoreType WasabiCoreType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FWasabiCharacterTraits CharacterTraits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		TArray<FWasabiEmotion> KnownEmotions;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "")
		UAIWasabiOriginalEngineCore* OriginalEngineCore;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "")
		UAIWasabiImprovedEngineCore* ImprovedEngineCore;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float JoyDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float DistressDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Testing")
		float JoyDistressCoeficient;

	UAIWasabiBaseEngineCore* EngineCore;

public:
	
	UAIWasabiEmotionEngine();
	
	virtual void InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
		virtual FAIEmotionState GetEmotionState() const override;

	FORCEINLINE UAIWasabiBaseEngineCore* GetEngineCore() const { return EngineCore; }

	UFUNCTION()
		virtual void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor) override; 

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);
};