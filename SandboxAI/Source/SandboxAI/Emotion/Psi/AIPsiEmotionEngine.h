// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "SandboxAI.h"
#include "PsiStructures.h"
#include "AIPsiEmotionKnowledge.h"
#include "../AIBaseEmotionEngine.h"
#include "AIPsiEmotionEngine.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIPsiEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SomeOtherName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		FAIEmotionState Emotions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		TArray<FPsiDrive> Drives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		TArray<FPsiMotivation> Motivations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		FPsiGoal Goal;


	UAIPsiEmotionKnowledge* knowledge;

public:
	UAIPsiEmotionEngine();
	/** Used to initialized emotion (knowledge and general) */
	virtual void InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge) override;
	/** Used to update emotion engine, emotion dynamic and emotion decay go here */
	virtual void TickEmotionEngine(float DeltaSeconds) override;
	/** Used to retrieve emotional state at any time, should be cheap to execute */
	virtual FAIEmotionState GetEmotiomState() const;
protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);

	virtual void ProcessPsiTheory();
	virtual void ProcessDrives();
	virtual void ProcessMotivations();
	virtual void ProcessGoal();
	//virtual void AffectEmotions(knowledge data);

};