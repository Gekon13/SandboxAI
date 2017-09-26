// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AIEmotionConstants.h"
#include "AIEmotionInformation.h"
#include "AIEmotionKnowledge.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIEmotionKnowledge : public UObject
{
	GENERATED_BODY()

public: //members // TODO: expand on this
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> AvailableActionNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAIEmotionInformation> Informations;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AActor* ControlledActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UGameplayComponent* ControlledGameplayComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Scale;

public: //methods
	UAIEmotionKnowledge();

	FORCEINLINE float GetScale() const { return Scale; }
	void SetScale(float newScale);
};