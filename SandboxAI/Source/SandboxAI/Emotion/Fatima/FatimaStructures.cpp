// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "FatimaStructures.h"


FFatimaEmotion::FFatimaEmotion(FString Name) :Name(Name) {
	Amount = 0;
	DecayFactor = 0.01f;
	AmountAfterEvent = 0;
	TimeOfEvent = 0;
	bContinuous = false;
}

FFatimaEmotions::FFatimaEmotions() {
	JoyDistress = FFatimaEmotion("Joy / Distress");
	HappyforResentment = FFatimaEmotion("Happyfor / Resentment");
	GloatingPity = FFatimaEmotion("Gloating / Pity");
	PrideShame = FFatimaEmotion("Pride / Shame");
	AdmirationReproach = FFatimaEmotion("Admiration / Reproach");
	GratificationRemorse = FFatimaEmotion("Gratification / Remorse");
	GratitudeAnger = FFatimaEmotion("Gratitude / Anger");
	LoveHate = FFatimaEmotion("Love / Hate");
	HopeFear = FFatimaEmotion("Hope / Fear");
	ReliefDisappointment = FFatimaEmotion("Relief / Disappointment");
	SatisfactionFearsconfirmed = FFatimaEmotion("Satisfaction / Fearsconfirmed");
}

FFatimaEmotion* FFatimaEmotions::FindEmotionWithName(FString Name) {
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

FFatimaAppraisal::FFatimaAppraisal(float Desirability, float DesirabilityForOthers, float Praiseworthiness, float Like, float GoalStatus, float GoalConduciveness, float GoalSucessProbability)
	:Desirability(Desirability), DesirabilityForOthers(DesirabilityForOthers), Praiseworthiness(Praiseworthiness), Like(Like),
	GoalStatus(GoalStatus), GoalConduciveness(GoalConduciveness), GoalSucessProbability(GoalSucessProbability) {}

FFatimaAppraisal FFatimaAppraisal::UpdateAppraisal(FFatimaAppraisal Appraisal, float DeltaTime) {
	UpdateEmotions(&Appraisal.Desirability, DeltaTime);
	UpdateEmotions(&Appraisal.DesirabilityForOthers, DeltaTime);
	UpdateEmotions(&Appraisal.Praiseworthiness, DeltaTime);
	UpdateEmotions(&Appraisal.Like, DeltaTime);
	UpdateEmotions(&Appraisal.GoalStatus, DeltaTime);
	UpdateEmotions(&Appraisal.GoalConduciveness, DeltaTime);
	UpdateEmotions(&Appraisal.GoalSucessProbability, DeltaTime);

	return Appraisal;
}

void FFatimaAppraisal::UpdateEmotions(float* Variable, float DeltaTime) {
	*Variable *= DeltaTime * 0.1f;
}

TArray<FFatimaEmotion> FFatimaAppraisal::GenerateEmotions() {
	auto Emotions = FFatimaEmotions();
	if (Desirability != 0) {
		Emotions.JoyDistress.Amount = Desirability;

		GeneratedEmotions.Add(Emotions.JoyDistress);
	}
	if (Desirability != 0 && DesirabilityForOthers != 0) {
		auto Factor = (Desirability + DesirabilityForOthers) / 2;
		Emotions.HappyforResentment.Amount = Factor;
		Emotions.GloatingPity.Amount = Factor;

		GeneratedEmotions.Add(Emotions.HappyforResentment);
		GeneratedEmotions.Add(Emotions.GloatingPity);
	}
	if (Praiseworthiness != 0) {
		Emotions.PrideShame.Amount = Praiseworthiness;
		Emotions.AdmirationReproach.Amount = Praiseworthiness;

		GeneratedEmotions.Add(Emotions.PrideShame);
		GeneratedEmotions.Add(Emotions.AdmirationReproach);
	}
	if (Desirability != 0 && Praiseworthiness != 0) {
		auto Factor = (Desirability + Praiseworthiness) / 2;
		Emotions.GratificationRemorse.Amount = Factor;
		Emotions.GratitudeAnger.Amount = Factor;

		GeneratedEmotions.Add(Emotions.GratificationRemorse);
		GeneratedEmotions.Add(Emotions.GratitudeAnger);
	}
	if (Like != 0) {
		Emotions.JoyDistress.Amount = Like;

		GeneratedEmotions.Add(Emotions.LoveHate);
	}
	if (GoalStatus != 0 || GoalConduciveness != 0 || GoalSucessProbability != 0) {
		auto Factor = (GoalStatus + GoalConduciveness + GoalSucessProbability) / 3;
		Emotions.HopeFear.Amount = Factor;
		Emotions.ReliefDisappointment.Amount = Factor;
		Emotions.SatisfactionFearsconfirmed.Amount = Factor;

		GeneratedEmotions.Add(Emotions.HopeFear);
		GeneratedEmotions.Add(Emotions.ReliefDisappointment);
		GeneratedEmotions.Add(Emotions.SatisfactionFearsconfirmed);
	}

	return GeneratedEmotions;
}

FFatimaGoal::FFatimaGoal(float* Variable, float SuccessValue, FString Description) :Description(Description), SuccessValue(SuccessValue), Variable(Variable) {
	if (Variable) {
		StartValue = *Variable;
	}
}
