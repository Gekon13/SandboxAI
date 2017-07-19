// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Appraisal.h"
#include "EmotionSourceComponent.generated.h"

/**
 * Gives owning actor a way to propagate emotions
 */
UCLASS(ClassGroup = (Emotions), HideCategories = (Activation, Collision, Cooking), meta = (BlueprintSpawnableComponent))
class SANDBOXAI_API UEmotionSourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEmotionSourceComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FAppraisal Appraisal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		bool bContinuous;

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
