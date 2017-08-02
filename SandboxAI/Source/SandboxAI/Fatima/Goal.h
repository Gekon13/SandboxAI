// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Goal.generated.h"

USTRUCT()
struct FGoal
{
	GENERATED_BODY()

public:
	FGoal() : FGoal(nullptr, 2.f, "Test") {}
	FGoal(float* Variable, float SuccessValue, FString Description);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SuccessValue;

	float* Variable;
	float StartValue;
};