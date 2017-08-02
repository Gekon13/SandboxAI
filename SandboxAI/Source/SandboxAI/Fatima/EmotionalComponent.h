// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Emotions.h"
#include "Appraisal.h"
#include "EmotionStimulusFatima.h"
#include "Goal.h"
#include "EmotionalComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSensorUpdatedDelegate, FAppraisal, Appraisal);

/**
* EmotionalComponent is used to register emotions from enviroment using FatiMA architecture
*/
UCLASS(ClassGroup = (Emotions), HideCategories = (Activation, Collision, Cooking), meta = (BlueprintSpawnableComponent))
class SANDBOXAI_API UEmotionalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEmotionalComponent();

	FSensorUpdatedDelegate OnSensorUpdated;

	void AddContinuousStimulus(FEmotionStimulusFatima EmotionStimulus);
	void RemoveContinuousStimulus(AActor* Instigator);
	void AddGoal(FGoal Goal) { Goals.Add(Goal); }

protected:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateEmotions(FAppraisal* Appraisal, float MoodFactor);
	void CalculateMood(float DeltaTime);
	void CalculateEmotion(FEmotion* Emotion, FEmotion* Personality) const;
	void UpdateActions() const;

	UFUNCTION()
		void OnEventUpdated(FAppraisal Appraisal);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FEmotions Personality;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions", meta = (ClampMin = "-11.0", ClampMax = "11.0"))
		float Mood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FEmotions Emotions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		TArray<FGoal> Goals;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (ClampMin = "0", ClampMax = "1.0"))
		float EmotionThreshold;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (ClampMin = "0"))
		float MoodDecrementAmount;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (ClampMin = "0", ClampMax = "1.0"))
		float MoodRelevance;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (ClampMin = "0"))
		float ContinuousEmotionsInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration", meta = (ClampMin = "0"))
		float GoalsInterval;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Actions", meta = (ClampMin = "0"))
		float SpeedFactor;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Visualization")
		FLinearColor EmotionColorMin;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Visualization")
		FLinearColor EmotionColorMax;

private:
	void SetEmotionContinuous(FAppraisal Appraisal, bool Continuous);
	void UpdateContinuousStimulus();
	void UpdateGoals();

	float MinMood, MaxMood, MinEmotion, MaxEmotion;
	float MinMovementSpeed, MaxMovementSpeed;
	class UCharacterMovementComponent* MovementComponent;
	TArray<FEmotionStimulusFatima> EmotionStimuluses;
	FTimerHandle ContinuousTimerHandle, GoalsTimerHandle;
};
