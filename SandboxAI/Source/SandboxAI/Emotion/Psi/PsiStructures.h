// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Common/AIEmotionConstants.h"
#include "../Common/AIEmotionPointPAD.h"
#include "PsiStructures.generated.h"



UENUM(BlueprintType)
enum class EPsiDrive : uint8
{
	ENone = 0 UMETA(DisplayName = "None"),
	ESafety = 1 UMETA(DisplayName = "Safety"),
};

UENUM(BlueprintType)
enum class EDriveCategory : uint8
{
	ECognitive = 0 UMETA(DisplayName = "Cognitive"),
	ESocial = 1 UMETA(DisplayName = "Social"),
	EPhysiological = 2 UMETA(DisplayName = "Physiological"),
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiPersonalityTrait
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0"))
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "2.0", UIMin = "0.0", UIMax = "2.0"))
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EEmotionName AffectedEmotion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EPsiDrive AffectedDrive;

public:
	FPsiPersonalityTrait() : Name(""), Value(1.0f), AffectedEmotion(EEmotionName::None), AffectedDrive(EPsiDrive::ENone) {}
	FPsiPersonalityTrait(FString name, float value, EEmotionName emotion = EEmotionName::None, EPsiDrive drive = EPsiDrive::ENone) : Name(name), Value(FMath::Clamp(value, 0.0f, 2.0f)), AffectedEmotion(emotion), AffectedDrive(drive) {}
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiGoal
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EPsiDrive Type;

public:
	FPsiGoal() : Value(0.0f), Type(EPsiDrive::ESafety) {}
	FPsiGoal(float value, EPsiDrive driveType) : Value(value), Type(driveType) {}
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiMotivation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EPsiDrive Type;

public:
	FPsiMotivation() : Value(0.0f), Type(EPsiDrive::ESafety) {}
	FPsiMotivation(float value, EPsiDrive driveType) : Value(value), Type(driveType){}

};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiDrive
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float Treshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	EPsiDrive Type;

public:
	FPsiDrive() : Value(0), Treshold(0), Type(EPsiDrive::ESafety) {}
	FPsiDrive(float value, float treshold, EPsiDrive type) : Value(value), Treshold(treshold), Type(type) {}
	bool CheckDriveState()
	{
		return Value >= Treshold;
	}

	FPsiMotivation GenerateMotivation()
	{
		return FPsiMotivation(Value, Type);
	}
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiEmotionToPad
{
	GENERATED_BODY()

public:
	EEmotionName EmotionName;
	FAIEmotionPointPAD Positive;
	FAIEmotionPointPAD Negative;
public:
	FPsiEmotionToPad() : EmotionName(EEmotionName::None), Positive(FAIEmotionPointPAD()), Negative(FAIEmotionPointPAD()){}
	FPsiEmotionToPad( EEmotionName emotion, FAIEmotionPointPAD positive, FAIEmotionPointPAD negative) : EmotionName(emotion), Positive(positive), Negative(negative) {}
	
};
/*
FVector Admiration = FVector(.4f, .3f, -.24f);
FVector Anger = FVector(-.51f, .59f, .25f);
FVector Disliking = FVector(-.4f, -.2f, .1f);
FVector Disappointment = FVector(-.3f, -.4f, -.4f);
FVector Distress = FVector(-.4f, .2f, .5f);
FVector Fear = FVector(-.64f, .6f, .43f);
FVector FearsConfirmed = FVector(-.5f, .3f, -.7f);
FVector Gloating = FVector(.3f, -.3f, -.1f);
FVector Gratification = FVector(.6f, -.3f, .4f);
FVector Gratitude = FVector(.2f, .5f, -.3f);
FVector HappyFor = FVector(.4f, -.2f, -.2f);
FVector Hate = FVector(-.4f, -.2f, .4f);
FVector Hope = FVector(.2f, .2f, -.1f);
FVector Joy = FVector(.4f, .2f, .1f);
FVector Liking = FVector(.4f, -.16f, -.24f);
FVector Love = FVector(.3f, .1f, .2f);
FVector Pity = FVector(-.4f, -.2f, -.5f);
FVector Pride = FVector(.4f, .3f, .3f);
FVector Relief = FVector(.2f, -.3f, -.4f);
FVector Remorse = FVector(-.3f, .1f, -.6f);
FVector Reproach = FVector(-.3f, -.1f, .4f);
FVector Resentment = FVector(-.2f, -.3f, -.2f);
FVector Satisfaction = FVector(.3f, -.2f, .4f);
FVector Shame = FVector(-.3f, .1f, -.6f);
*/