// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PsiEmotions.h"
#include "../Emotion/Psi/PsiStructures.h"
#include "FixedPath/SandboxAISplineAIController.h"
#include "PsiAIController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API APsiAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	class UPsiEmotions* PsiEmotionsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	TArray<FPsiDrive> Drives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	TArray<FPsiMotivation> Motivations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	FPsiGoal Goal;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
	//TArray<FKnowledgeStruct> Knowledge;

public:

	typedef void (APsiAIController::*FunctionPtrType)(float);

	APsiAIController();

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void ProcessPsiTheory();
	virtual void ProcessDrives();
	virtual void ProcessMotivations();
	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement) override;
	virtual void MoveSlower(float value);
	virtual void MoveFaster(float value);
	
};