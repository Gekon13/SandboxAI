// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "Emotions.h"


FEmotion::FEmotion(FString Name) :Name(Name) {
	Amount = 0;
	DecayFactor = 0.01f;
	AmountAfterEvent = 0;
	TimeOfEvent = 0;
	bContinuous = false;
}

FEmotions::FEmotions() {
	JoyDistress = FEmotion("Joy / Distress");
	HappyforResentment = FEmotion("Happyfor / Resentment");
	GloatingPity = FEmotion("Gloating / Pity");
	PrideShame = FEmotion("Pride / Shame");
	AdmirationReproach = FEmotion("Admiration / Reproach");
	GratificationRemorse = FEmotion("Gratification / Remorse");
	GratitudeAnger = FEmotion("Gratitude / Anger");
	LoveHate = FEmotion("Love / Hate");
	HopeFear = FEmotion("Hope / Fear");
	ReliefDisappointment = FEmotion("Relief / Disappointment");
	SatisfactionFearsconfirmed = FEmotion("Satisfaction / Fearsconfirmed");
}

FEmotion* FEmotions::FindEmotionWithName(FString Name) {
	if (JoyDistress.Name == Name) {
		return &JoyDistress;
	}
	if (HappyforResentment.Name == Name) {
		return &HappyforResentment;
	}
	if (GloatingPity.Name == Name) {
		return &GloatingPity;
	}
	if (PrideShame.Name == Name) {
		return &PrideShame;
	}
	if (AdmirationReproach.Name == Name) {
		return &AdmirationReproach;
	}
	if (GratificationRemorse.Name == Name) {
		return &GratificationRemorse;
	}
	if (GratitudeAnger.Name == Name) {
		return &GratitudeAnger;
	}
	if (LoveHate.Name == Name) {
		return &LoveHate;
	}
	if (HopeFear.Name == Name) {
		return &HopeFear;
	}
	if (ReliefDisappointment.Name == Name) {
		return &ReliefDisappointment;
	}
	if (SatisfactionFearsconfirmed.Name == Name) {
		return &SatisfactionFearsconfirmed;
	}

	return nullptr;
}
