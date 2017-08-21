// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AISimplexStructures.h"
#include "Emotion/AIEmotionConstants.h"
#include "AISimplexAppraisalModule.generated.h"

class UAIEmotionKnowledge;

/**
 * OCC based appraisal module for SIMPLEX model
 */
UCLASS()
class SANDBOXAI_API UAISimplexAppraisalModule : public UObject
{
	GENERATED_BODY()
	
protected:
	FSimplexPersonality* Personality;
	UAIEmotionKnowledge* Knowledge;
	UAIEmotionKnowledge* Memory;
	AActor* Owner;

protected:
	FSimplexPADPoint Internal_DoAppraisalForConsequences(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor);
	FSimplexPADPoint Internal_DoAppraisalForActions(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor);
	FSimplexPADPoint Internal_DoAppraisalForObjects(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor);

public:
	TArray<FSimplexPADPoint> DoAppraisal(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor);

	FORCEINLINE void InitializeAppraisalModule(UAIEmotionKnowledge* InEmotionKnowlege, UAIEmotionKnowledge* InMemory, FSimplexPersonality* InPersonality, AActor* InOwner)
	{
		Knowledge = InEmotionKnowlege;
		Memory = InMemory;
		Personality = InPersonality;
		Owner = InOwner;
	}
};
