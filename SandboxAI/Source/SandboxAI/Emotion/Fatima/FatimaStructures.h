// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "../Common/AIEmotionConstants.h"
#include "Emotion/Common/AIEmotionPointPAD.h"
#include "FatimaStructures.generated.h"

struct FFatimaEmotions;

USTRUCT()
struct FFatimaToPAD
{
	GENERATED_BODY()

public:
	static FAIEmotionPointPAD Admiration;
	static FAIEmotionPointPAD Anger;
	static FAIEmotionPointPAD Disliking;
	static FAIEmotionPointPAD Disappointment;
	static FAIEmotionPointPAD Distress;
	static FAIEmotionPointPAD Fear;
	static FAIEmotionPointPAD FearsConfirmed;
	static FAIEmotionPointPAD Gloating;
	static FAIEmotionPointPAD Gratification;
	static FAIEmotionPointPAD Gratitude;
	static FAIEmotionPointPAD HappyFor;
	static FAIEmotionPointPAD Hate;
	static FAIEmotionPointPAD Hope;
	static FAIEmotionPointPAD Joy;
	static FAIEmotionPointPAD Liking;
	static FAIEmotionPointPAD Love;
	static FAIEmotionPointPAD Pity;
	static FAIEmotionPointPAD Pride;
	static FAIEmotionPointPAD Relief;
	static FAIEmotionPointPAD Remorse;
	static FAIEmotionPointPAD Reproach;
	static FAIEmotionPointPAD Resentment;
	static FAIEmotionPointPAD Satisfaction;
	static FAIEmotionPointPAD Shame;
};

USTRUCT()
struct FFatimaEmotion
{
	GENERATED_BODY()

public:
	FFatimaEmotion() : FFatimaEmotion(EEmotionPairName::None) {}
	FFatimaEmotion(const EEmotionPairName Name) :FFatimaEmotion(Name, 0.f) {}
	FFatimaEmotion(EEmotionPairName Name, float Value, FAIEmotionPointPAD PositivePoint = FAIEmotionPointPAD(), FAIEmotionPointPAD NegativePoint = FAIEmotionPointPAD());
	FFatimaEmotion(const EEmotionPairName Name, const FAIEmotionPointPAD PositivePoint, const FAIEmotionPointPAD NegativePoint) :FFatimaEmotion(Name, 0.f, PositivePoint, NegativePoint) {}
	void AddToPAD(TArray<FVector>* EmotionsInPAD, FFatimaEmotions* Personality) const;

	static float MinEmotion, MaxEmotion, EmotionDiff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "-1.0", ClampMax = "1.0"))
		float Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float DecayFactor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float Threshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		bool bCalculateInPAD;

	EEmotionPairName Name;
	float AmountAfterEvent, TimeOfEvent;
	bool bContinuous;
	FAIEmotionPointPAD PositivePoint, NegativePoint;
};

USTRUCT()
struct FFatimaEmotions
{
	GENERATED_BODY()

public:
	FFatimaEmotions();
	FFatimaEmotion* FindEmotionWithName(EEmotionPairName Name);

	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion JoyDistress;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion HappyforPitty;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion AdmirationGloating;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion PrideShame;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion ConcentrationBore;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion AngerRemorse;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion GratitudeResentment;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion LoveHate;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion HopeFear;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion ReliefFearsConfirmed;
	UPROPERTY(EditAnywhere, Category = "Emotion")
		FFatimaEmotion SatisfactionDisapointment;

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
