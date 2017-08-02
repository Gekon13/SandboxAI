// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "ReactsToEmotions.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UReactsToEmotions : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class SANDBOXAI_API IReactsToEmotions
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpdateEmotionVisual(FLinearColor Color);
};
