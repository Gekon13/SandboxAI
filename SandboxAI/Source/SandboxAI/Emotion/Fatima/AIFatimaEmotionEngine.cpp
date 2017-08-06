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

void UAIFatimaEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge) {
	Super::InitializeEmotionEngine(emotionKnowledge);

	GetOuter()->GetWorld()->GetTimerManager().SetTimer(GoalsTimerHandle, this, &UAIFatimaEmotionEngine::UpdateGoals, GoalsInterval, true);
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
	auto Appraisal = FFatimaAppraisal(value, 0, 0, 0, 0, 0, 0);
	OnEventUpdated(Appraisal);
}

void UAIFatimaEmotionEngine::UpdateEmotions(FFatimaAppraisal* Appraisal, float MoodFactor) {
	auto GeneratedEmotions = Appraisal->GenerateEmotions();
	for (auto AppraisalEmotion : GeneratedEmotions) {
		auto Emotion = Emotions.FindEmotionWithName(AppraisalEmotion.Name);
		if (Emotion) {
			auto OldValue = Emotion->Amount;
			Emotion->Amount = FMath::Clamp(Emotion->Amount + AppraisalEmotion.Amount + MoodFactor, MinEmotion, MaxEmotion);
			Emotion->AmountAfterEvent = Emotion->Amount;
			Emotion->TimeOfEvent = GetOuter()->GetWorld()->GetTimeSeconds();
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

void UAIFatimaEmotionEngine::CalculateEmotion(FFatimaEmotion* Emotion, FFatimaEmotion* PersonalityEmotion) const {
	if (Emotion->Amount != PersonalityEmotion->Amount && !Emotion->bContinuous) {
		auto CurrentTime = GetOuter()->GetWorld()->GetTimeSeconds() - Emotion->TimeOfEvent;
		Emotion->Amount = FMath::Clamp(Emotion->AmountAfterEvent * (FMath::Exp(-Emotion->DecayFactor * CurrentTime - PersonalityEmotion->Amount) + PersonalityEmotion->Amount), MinEmotion, MaxEmotion);
		if (FMath::Abs(Emotion->Amount - PersonalityEmotion->Amount) <= EmotionThreshold) {
			Emotion->Amount = PersonalityEmotion->Amount;
		}
	}
}

void UAIFatimaEmotionEngine::UpdateActions() {
	auto EmotionCoefficient = (Emotions.JoyDistress.Amount - MinEmotion) / (MaxEmotion - MinEmotion);
	auto CurrentSpeed = 1 - EmotionCoefficient;
	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], CurrentSpeed));
}

void UAIFatimaEmotionEngine::OnEventUpdated(FFatimaAppraisal Appraisal) {
	auto MoodFactor = Mood * MoodRelevance / MaxMood;
	UpdateEmotions(&Appraisal, MoodFactor);
}

void UAIFatimaEmotionEngine::UpdateGoals() {
	for (auto Goal : Goals) {
		auto GoalStatus = (*Goal.Variable - Goal.StartValue) / (Goal.SuccessValue - Goal.StartValue);
		auto Appraisal = FFatimaAppraisal::UpdateAppraisal(FFatimaAppraisal(0, 0, 0, 0, GoalStatus, 0, 0), GoalsInterval);
		OnEventUpdated(Appraisal);
	}
}
