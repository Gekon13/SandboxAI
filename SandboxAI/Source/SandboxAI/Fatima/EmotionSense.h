// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Appraisal.h"
#include "EmotionSense.generated.h"

/**
 *
 */
UCLASS(ClassGroup = Emotions, Config = Game)
class SANDBOXAI_API UEmotionSense : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Emotions", meta = (WorldContext = "WorldContext"))
		static void ReportEmotionEventToAll(UObject* WorldContext, FAppraisal Apprasial, AActor* Instigator = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Emotions")
		static void ReportEmotionEventToActor(FAppraisal Apprasial, AActor* Actor, AActor* Instigator = nullptr);

private:
	static void BrodcastApprasial(FAppraisal Apprasial, AActor* Actor);

};
