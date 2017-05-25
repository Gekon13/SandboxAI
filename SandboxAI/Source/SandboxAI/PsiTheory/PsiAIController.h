// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PsiEmotions.h"
#include "PsiStructures.h"
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
	class UPsiEmotions* PsiEmotionsComponent;
	FPsiDrives PsiDrives;
	FPsiMotivations PsiMotivations;
	FPsiGoal PsiGoal;

public:
	APsiAIController();

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void ProcessPsiTheory();
	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement) override;
	virtual void MoveSlower(float value);
	virtual void MoveFaster(float value);
	
};
