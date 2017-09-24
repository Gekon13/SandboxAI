// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Emotion/Containers/AIEmotionConstants.h"
#include "SimplexLogger.generated.h"

class UAIEmotionComponent;
class UAISimplexEmotionEngine;

USTRUCT()
struct FSimplexLoggerInfo
{
	GENERATED_BODY()

protected:
	UAISimplexEmotionEngine* SimplexEmotionEngine;

public:
	UPROPERTY(EditAnywhere, Category = "LoggerInfo")
		FString SampleName;

	UPROPERTY(EditAnywhere, Category = "LoggerInfo")
		APawn* PawnToLog;

public:
	void Initialize();

	float GetEmotionalDeviation() const;
	float GetEmotionPair(EEmotionPairName EmotionPair) const;
	float GetRunSpeed() const;
};

UCLASS()
class SANDBOXAI_API ASimplexLogger : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Logger")
		TArray<FSimplexLoggerInfo> LoggerInfo;

	UPROPERTY(EditAnywhere, Category = "Logger")
		FString LogName;

	UPROPERTY(EditAnywhere, Category = "Logger")
		float LogEverySeconds;

	UPROPERTY(EditAnywhere, Category = "Logger")
		bool bEmotionDeviation;

	UPROPERTY(EditAnywhere, Category = "Logger")
		bool bRun;

	FString LogText;
	float Timer;
	uint64 LogI;

public:	
	// Sets default values for this actor's properties
	ASimplexLogger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Logger")
		void SaveToFile();
};
