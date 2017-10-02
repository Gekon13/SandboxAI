// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Common/AIEmotionConstants.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EEmotionName AffectedEmotion;

public:
	FPsiPersonalityTrait() : Name(""), Value(0.0f), AffectedEmotion(EEmotionName::None) {}
	FPsiPersonalityTrait(FString name, float value, EEmotionName emotion ) : Name(name), Value(value), AffectedEmotion(emotion) {}
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
