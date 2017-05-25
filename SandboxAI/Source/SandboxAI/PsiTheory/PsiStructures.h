// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PsiStructures.generated.h"

UENUM(BlueprintType)
enum class EPsiDrive : uint8
{
	ESafety = 0 UMETA(DisplayName = "Safety"),
	ECuriosity = 1 UMETA(DisplayName = "Curiosity"),
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
	//bool IsAfecting(EPsiDrive type);
	//void Affect(float value);
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
struct SANDBOXAI_API FPsiMotivations
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPsiMotivation> Motivations;

	FPsiGoal GenerateGoal()
	{
		int index = 0;
		for (int i = 1; i < Motivations.Num(); ++i)
		{
			if (Motivations[i].Value > Motivations[index].Value)
				index = i;
		}
		return FPsiGoal(Motivations[index].Value, Motivations[index].Type);
	}
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiDrives
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPsiDrive> Drives;

public:
	FPsiDrives()
	{
		Drives.Add(FPsiDrive(0.0f, 0.3f, EPsiDrive::ESafety));
		Drives.Add(FPsiDrive(0.0f, 0.0f, EPsiDrive::ECuriosity));
	}

	TArray<FPsiMotivation> GenerateMotivations()
	{
		TArray<FPsiMotivation> motivations = TArray<FPsiMotivation>();
		for (int i = 0; i < Drives.Num(); ++i)
		{
			if (Drives[i].CheckDriveState())
				motivations.Add(Drives[i].GenerateMotivation());
		}
		return motivations;
	}
};
