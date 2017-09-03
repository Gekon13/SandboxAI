// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"
#include "WasabiStateLogger.generated.h"

class UAIWasabiEmotionEngine;
class UAIEmotionComponent;

USTRUCT(BlueprintType)
struct SANDBOXAI_API FLogTarget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LogName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APawn* LogTarget;

};

UCLASS()
class SANDBOXAI_API AWasabiStateLogger : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger")
		FString LogFilePrefix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger")
		bool bCumulateInputValency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger")
		TArray<FLogTarget> LogTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger", meta = (ClampMin=1, ClampMax=60, UIMin=1, UIMax=60))
		int32 PrintEvery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger")
		FColor LogColor;

public:	
	AWasabiStateLogger();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
		void SaveFile();

	UFUNCTION(BlueprintCallable)
		void SaveFileHorizontal();

protected:
	float _cooldownTimer;
	float _cooldownLength;
	bool _bCanLogToFile;

	static UAIEmotionComponent* GetEmotionComponent(APawn* pawnToInspect);
	static UAIWasabiEmotionEngine* GetWasabiEmotionEngine(APawn* pawnToInspect);
};
