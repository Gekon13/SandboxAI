// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SandboxAIGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API USandboxAIGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bShowGizmos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bShowSightGizmos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bShowHearingGizmos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bShowLogs;

public:
	USandboxAIGameInstance();
	
	FORCEINLINE const bool ShouldShowGizmos() const { return bShowGizmos; }
	FORCEINLINE const bool ShouldShowSightGizmos() const { return bShowSightGizmos; }
	FORCEINLINE const bool ShouldShowHearingGizmos() const { return bShowHearingGizmos; }
	FORCEINLINE const bool ShouldShowLogs() const { return bShowLogs; }
};
