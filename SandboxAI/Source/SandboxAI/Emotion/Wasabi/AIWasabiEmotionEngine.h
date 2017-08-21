// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "AIWasabiEmotionEngine.generated.h"

class UAIWasabiBaseEngineCore;
class UAIWasabiOriginalEngineCore;

UCLASS(BlueprintType)
class PROJECT_API UAIWasabiEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString SomeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
		FString SomeOtherName;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = "Core")
		UAIWasabiOriginalEngineCore* OriginalEngineCore;

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
	virtual FAIEmotionState GetEmotionState() const override;

	FORCEINLINE UAIWasabiBaseEngineCore* GetEngineCore() const { return EngineCore; }

	UFUNCTION()
		virtual void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor) override; 

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);
};