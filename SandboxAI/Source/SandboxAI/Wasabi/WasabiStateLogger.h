// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WasabiStateLogger.generated.h"

UCLASS()
class SANDBOXAI_API AWasabiStateLogger : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logger")
		FString LogFilePrefix;

public:	
	AWasabiStateLogger();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
		void SaveFile();

};
