// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AIBaseEmotionEngine.h"
#include "FatimaStructures.h"
#include "Fatima/EmotionStimulusFatima.h"
#include "AIFatimaEmotionEngine.generated.h"

UCLASS(BlueprintType)
class PROJECT_API UAIFatimaEmotionEngine : public UAIBaseEmotionEngine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FFatimaEmotions Personality;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions", meta = (ClampMin = "-11.0", ClampMax = "11.0"))
		float Mood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Emotions")
		FFatimaEmotions Emotions;
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		TArray<FGoal> Goals;*/
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

	UAIFatimaEmotionEngine();

	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge) override;
	virtual void TickEmotionEngine(float DeltaSeconds) override;

protected:
	virtual float GetEngineScale() const override;

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);

	void UpdateEmotions(FFatimaAppraisal* Appraisal, float MoodFactor);
	void CalculateMood(float DeltaTime);
	void CalculateEmotion(FFatimaEmotion* Emotion, FFatimaEmotion* Personality) const;
	void UpdateActions() const;

private:
	void SetEmotionContinuous(FFatimaAppraisal Appraisal, bool Continuous);
	void UpdateContinuousStimulus();
	//void UpdateGoals();

	float MinMood, MaxMood, MinEmotion, MaxEmotion;
	float MinMovementSpeed, MaxMovementSpeed;
	class UCharacterMovementComponent* MovementComponent;
	TArray<FEmotionStimulusFatima> EmotionStimuluses;
	FTimerHandle ContinuousTimerHandle, GoalsTimerHandle;
};