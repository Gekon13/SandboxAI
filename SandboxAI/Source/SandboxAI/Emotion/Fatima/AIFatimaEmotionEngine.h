// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "FatimaStructures.h"
#include "AIFatimaEmotionEngine.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIFatimaEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

public:
	UAIFatimaEmotionEngine();

	void InitializeEmotionEngine(UAIEmotionKnowledge* Knowledge) override;
	void TickEmotionEngine(float DeltaSeconds) override;
	void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor) override;
	void AddGoal(FFatimaGoal Goal) { Goals.Add(Goal); }

protected:
	float GetEngineScale() const override;
	void DirectValencedImpulseInternal(float Value, bool bContinuous) override;

	void UpdateEmotions(FFatimaAppraisal* Appraisal);
	void AppraisalEmotions(TArray<FAIEmotionDelta> EmotionDeltas);
	void CalculateMood(float DeltaTime);
	void CalculateEmotion(FFatimaEmotion* Emotion, FFatimaEmotion* PersonalityEmotion) const;
	void UpdateActions();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FFatimaEmotions Personality;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions", meta = (ClampMin = "-11.0", ClampMax = "11.0"))
		float Mood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FFatimaEmotions Emotions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		TArray<FFatimaGoal> Goals;
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

private:
	void UpdateEmotion(const float MoodFactor, const FFatimaEmotion AppraisalEmotion);
	void UpdateGoals();

	float MinMood, MaxMood, MinEmotion, MaxEmotion;
	FTimerHandle ContinuousTimerHandle, GoalsTimerHandle;
};