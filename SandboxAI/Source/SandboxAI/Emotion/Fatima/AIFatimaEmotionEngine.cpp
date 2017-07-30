// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIFatimaEmotionEngine.h"

UAIFatimaEmotionEngine::UAIFatimaEmotionEngine() {
	Mood = 0;
	MinMood = -11.f;
	MaxMood = 11.f;
	MinEmotion = -1.f;
	MaxEmotion = 1.f;

	EmotionThreshold = 0.005f;
	MoodDecrementAmount = 0.005f;
	MoodRelevance = 0.1f;
	ContinuousEmotionsInterval = 0.1f;
	GoalsInterval = 0.5f;

	SpeedFactor = 1.5f;
}

void UAIFatimaEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge) {
	Super::InitializeEmotionEngine(emotionKnowledge);
}

void UAIFatimaEmotionEngine::TickEmotionEngine(float DeltaSeconds) {
	Super::TickEmotionEngine(DeltaSeconds);

	CalculateMood(DeltaSeconds);
	CalculateEmotion(&Emotions.JoyDistress, &Personality.JoyDistress);
	CalculateEmotion(&Emotions.HappyforResentment, &Personality.HappyforResentment);
	CalculateEmotion(&Emotions.GloatingPity, &Personality.GloatingPity);
	CalculateEmotion(&Emotions.PrideShame, &Personality.PrideShame);
	CalculateEmotion(&Emotions.AdmirationReproach, &Personality.AdmirationReproach);
	CalculateEmotion(&Emotions.GratificationRemorse, &Personality.GratificationRemorse);
	CalculateEmotion(&Emotions.GratitudeAnger, &Personality.GratitudeAnger);
	CalculateEmotion(&Emotions.LoveHate, &Personality.LoveHate);
	CalculateEmotion(&Emotions.HopeFear, &Personality.HopeFear);
	CalculateEmotion(&Emotions.ReliefDisappointment, &Personality.ReliefDisappointment);
	CalculateEmotion(&Emotions.SatisfactionFearsconfirmed, &Personality.SatisfactionFearsconfirmed);
	UpdateActions();
}

float UAIFatimaEmotionEngine::GetEngineScale() const {
	return 1.0f;
}

void UAIFatimaEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous) {
	// this method handles stuff like bonfires
}

void UAIFatimaEmotionEngine::UpdateEmotions(FFatimaAppraisal* Appraisal, float MoodFactor) {
	auto GeneratedEmotions = Appraisal->GenerateEmotions();
	for (auto AppraisalEmotion : GeneratedEmotions) {
		auto Emotion = Emotions.FindEmotionWithName(AppraisalEmotion.Name);
		if (Emotion) {
			auto OldValue = Emotion->Amount;
			Emotion->Amount = FMath::Clamp(Emotion->Amount + AppraisalEmotion.Amount + MoodFactor, MinEmotion, MaxEmotion);
			Emotion->AmountAfterEvent = Emotion->Amount;
			Emotion->TimeOfEvent = GetWorld()->GetTimeSeconds();
			Mood = FMath::Clamp(Mood + Emotion->Amount - OldValue, MinMood, MaxMood);
		}
	}
}

void UAIFatimaEmotionEngine::CalculateMood(float DeltaTime) {
	if (Mood != 0) {
		if (Mood > 0) {
			Mood = FMath::Clamp(Mood - DeltaTime * MoodDecrementAmount, 0.f, MaxMood);
		} else {
			Mood = FMath::Clamp(Mood + DeltaTime * MoodDecrementAmount, MinMood, 0.f);
		}
	}
}

void UAIFatimaEmotionEngine::CalculateEmotion(FFatimaEmotion* Emotion, FFatimaEmotion* Personality) const {
	if (Emotion->Amount != Personality->Amount && !Emotion->bContinuous) {
		auto CurrentTime = GetWorld()->GetTimeSeconds() - Emotion->TimeOfEvent;
		Emotion->Amount = FMath::Clamp(Emotion->AmountAfterEvent * (FMath::Exp(-Emotion->DecayFactor * CurrentTime - Personality->Amount) + Personality->Amount), MinEmotion, MaxEmotion);
		if (FMath::Abs(Emotion->Amount - Personality->Amount) <= EmotionThreshold) {
			Emotion->Amount = Personality->Amount;
		}
	}
}

void UAIFatimaEmotionEngine::UpdateActions() const {
	auto EmotionCoefficient = (Emotions.JoyDistress.Amount - MinEmotion) / (MaxEmotion - MinEmotion);
	if (MovementComponent) {
		auto CurrentSpeed = FMath::Lerp<float>(MinMovementSpeed, MaxMovementSpeed, 1 - EmotionCoefficient);
		MovementComponent->MaxWalkSpeed = CurrentSpeed;
	}
}