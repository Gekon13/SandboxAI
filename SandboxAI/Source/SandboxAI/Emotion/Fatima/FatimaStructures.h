// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "FatimaStructures.generated.h"

USTRUCT()
struct FFatimaEmotion
{
	GENERATED_BODY()

public:
	FFatimaEmotion() : FFatimaEmotion("Test") {}
	FFatimaEmotion(FString Name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float DecayFactor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		FString Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float AmountAfterEvent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float TimeOfEvent;

	bool bContinuous;
};

USTRUCT()
struct FFatimaEmotions
{
	GENERATED_BODY()

public:
	FFatimaEmotions();
	FFatimaEmotion* FindEmotionWithName(FString Name);

	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion JoyDistress;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion HappyforResentment;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion GloatingPity;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion PrideShame;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion AdmirationReproach;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion GratificationRemorse;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion GratitudeAnger;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion LoveHate;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion HopeFear;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion ReliefDisappointment;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion SatisfactionFearsconfirmed;

};

USTRUCT(BlueprintType)
struct FFatimaAppraisal
{
	GENERATED_BODY()

public:
	FFatimaAppraisal() : FFatimaAppraisal(0.2f) {}
	FFatimaAppraisal(float Value) : FFatimaAppraisal(Value, Value, Value, Value, Value, Value, Value) {}
	FFatimaAppraisal(float Desirability, float DesirabilityForOthers, float Praiseworthiness, float Like, float GoalStatus, float GoalConduciveness, float GoalSucessProbability);

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

	static FFatimaAppraisal UpdateAppraisal(FFatimaAppraisal Appraisal, float DeltaTime);
	TArray<FFatimaEmotion> GenerateEmotions();

private:
	static void UpdateEmotions(float* Variable, float DeltaTime);
	TArray<FFatimaEmotion> GeneratedEmotions;
};

USTRUCT()
struct FFatimaGoal
{
	GENERATED_BODY()

public:
	FFatimaGoal() : FFatimaGoal(nullptr, 2.f, "Test") {}
	FFatimaGoal(float* Variable, float SuccessValue, FString Description);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SuccessValue;

	float* Variable;
	float StartValue;
};
