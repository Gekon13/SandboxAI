// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Emotions.h"
#include "Appraisal.generated.h"

USTRUCT(BlueprintType)
struct FAppraisal
{
	GENERATED_BODY()

public:
	FAppraisal() : FAppraisal(0.2f) {}
	FAppraisal(float Value) : FAppraisal(Value, Value, Value, Value, Value, Value, Value) {}
	FAppraisal(float Desirability, float DesirabilityForOthers, float Praiseworthiness, float Like, float GoalStatus, float GoalConduciveness, float GoalSucessProbability);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Desirability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float DesirabilityForOthers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Praiseworthiness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Like;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float GoalStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float GoalConduciveness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float GoalSucessProbability;

	static FAppraisal UpdateAppraisal(FAppraisal Appraisal, float DeltaTime);
	TArray<FEmotion> GenerateEmotions();

private:
	static void UpdateEmotions(float* Variable, float DeltaTime);
	TArray<FEmotion> GeneratedEmotions;
};
