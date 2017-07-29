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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeOtherName;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
		UAIWasabiOriginalEngineCore* OriginalEngineCore;

	UAIWasabiBaseEngineCore* EngineCore;

public:
	
	UAIWasabiEmotionEngine();
	
	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

	FORCEINLINE UAIWasabiBaseEngineCore* GetEngineCore() const { return EngineCore; }

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);
};