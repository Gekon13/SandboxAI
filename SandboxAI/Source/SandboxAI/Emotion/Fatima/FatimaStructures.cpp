// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "FatimaStructures.h"

//Mapping of OCC emotions into PAD space - Are Computer-Generated Emotions and Moods Plausible to Humans?
FAIEmotionPointPAD FFatimaToPAD::Admiration = FAIEmotionPointPAD(.4f, .3f, -.24f);
FAIEmotionPointPAD FFatimaToPAD::Anger = FAIEmotionPointPAD(-.51f, .59f, .25f);
FAIEmotionPointPAD FFatimaToPAD::Disliking = FAIEmotionPointPAD(-.4f, -.2f, .1f);
FAIEmotionPointPAD FFatimaToPAD::Disappointment = FAIEmotionPointPAD(-.3f, -.4f, -.4f);
FAIEmotionPointPAD FFatimaToPAD::Distress = FAIEmotionPointPAD(-.4f, .2f, .5f);
FAIEmotionPointPAD FFatimaToPAD::Fear = FAIEmotionPointPAD(-.64f, .6f, .43f);
FAIEmotionPointPAD FFatimaToPAD::FearsConfirmed = FAIEmotionPointPAD(-.5f, .3f, -.7f);
FAIEmotionPointPAD FFatimaToPAD::Gloating = FAIEmotionPointPAD(.3f, -.3f, -.1f);
FAIEmotionPointPAD FFatimaToPAD::Gratification = FAIEmotionPointPAD(.6f, -.3f, .4f);
FAIEmotionPointPAD FFatimaToPAD::Gratitude = FAIEmotionPointPAD(.2f, .5f, -.3f);
FAIEmotionPointPAD FFatimaToPAD::HappyFor = FAIEmotionPointPAD(.4f, -.2f, -.2f);
FAIEmotionPointPAD FFatimaToPAD::Hate = FAIEmotionPointPAD(-.4f, -.2f, .4f);
FAIEmotionPointPAD FFatimaToPAD::Hope = FAIEmotionPointPAD(.2f, .2f, -.1f);
FAIEmotionPointPAD FFatimaToPAD::Joy = FAIEmotionPointPAD(.4f, .2f, .1f);
FAIEmotionPointPAD FFatimaToPAD::Liking = FAIEmotionPointPAD(.4f, -.16f, -.24f);
FAIEmotionPointPAD FFatimaToPAD::Love = FAIEmotionPointPAD(.3f, .1f, .2f);
FAIEmotionPointPAD FFatimaToPAD::Pity = FAIEmotionPointPAD(-.4f, -.2f, -.5f);
FAIEmotionPointPAD FFatimaToPAD::Pride = FAIEmotionPointPAD(.4f, .3f, .3f);
FAIEmotionPointPAD FFatimaToPAD::Relief = FAIEmotionPointPAD(.2f, -.3f, -.4f);
FAIEmotionPointPAD FFatimaToPAD::Remorse = FAIEmotionPointPAD(-.3f, .1f, -.6f);
FAIEmotionPointPAD FFatimaToPAD::Reproach = FAIEmotionPointPAD(-.3f, -.1f, .4f);
FAIEmotionPointPAD FFatimaToPAD::Resentment = FAIEmotionPointPAD(-.2f, -.3f, -.2f);
FAIEmotionPointPAD FFatimaToPAD::Satisfaction = FAIEmotionPointPAD(.3f, -.2f, .4f);
FAIEmotionPointPAD FFatimaToPAD::Shame = FAIEmotionPointPAD(-.3f, .1f, -.6f);

float FFatimaEmotion::MinEmotion = -1.f;
float FFatimaEmotion::MaxEmotion = 1.f;
float FFatimaEmotion::EmotionDiff = MaxEmotion - MinEmotion;

FFatimaEmotion::FFatimaEmotion(EEmotionPairName Name, float Value, FAIEmotionPointPAD PositivePoint, FAIEmotionPointPAD NegativePoint) :Amount(Value), Name(Name), PositivePoint(PositivePoint), NegativePoint(NegativePoint) {
	DecayFactor = 0.01f;
	Threshold = 0.01f;
	AmountAfterEvent = 0;
	TimeOfEvent = 0;
	bContinuous = false;
	bCalculateInPAD = false;
}

void FFatimaEmotion::AddToPAD(TArray<FVector>* EmotionsInPAD, FFatimaEmotions* Personality) const {
	const auto PersonalityEmotion = Personality->FindEmotionWithName(Name);
	if (PersonalityEmotion->bCalculateInPAD) {
		const auto EmotionCoefficient = (Amount - MinEmotion) / EmotionDiff;
		const auto Point = FMath::Lerp(NegativePoint, PositivePoint, EmotionCoefficient);
		EmotionsInPAD->Add(Point);
	}
}

FFatimaEmotions::FFatimaEmotions() {
	JoyDistress = FFatimaEmotion(EEmotionPairName::Joy_Distress, FFatimaToPAD::Joy, FFatimaToPAD::Distress);
	HappyforPitty = FFatimaEmotion(EEmotionPairName::Happyfor_Pitty, FFatimaToPAD::HappyFor, FFatimaToPAD::Pity);
	AdmirationGloating = FFatimaEmotion(EEmotionPairName::Admiration_Gloating, FFatimaToPAD::Admiration, FFatimaToPAD::Gloating);
	PrideShame = FFatimaEmotion(EEmotionPairName::Pride_Shame, FFatimaToPAD::Pride, FFatimaToPAD::Shame);
	ConcentrationBore = FFatimaEmotion(EEmotionPairName::Concentration_Bore, FFatimaToPAD::Gratification, FFatimaToPAD::Reproach);
	AngerRemorse = FFatimaEmotion(EEmotionPairName::Anger_Remorse, FFatimaToPAD::Anger, FFatimaToPAD::Remorse);
	GratitudeResentment = FFatimaEmotion(EEmotionPairName::Gratitude_Resentment, FFatimaToPAD::Gratitude, FFatimaToPAD::Resentment);
	LoveHate = FFatimaEmotion(EEmotionPairName::Love_Hate, FFatimaToPAD::Love, FFatimaToPAD::Hate);
	HopeFear = FFatimaEmotion(EEmotionPairName::Hope_Fear, FFatimaToPAD::Hope, FFatimaToPAD::Fear);
	ReliefFearsConfirmed = FFatimaEmotion(EEmotionPairName::Relief_FearsConfirmed, FFatimaToPAD::Relief, FFatimaToPAD::FearsConfirmed);
	SatisfactionDisapointment = FFatimaEmotion(EEmotionPairName::Satisfaction_Disapointment, FFatimaToPAD::Satisfaction, FFatimaToPAD::Disappointment);
}

FFatimaEmotion* FFatimaEmotions::FindEmotionWithName(EEmotionPairName Name) {
	if (JoyDistress.Name == Name) {
		return &JoyDistress;
	}
	if (HappyforPitty.Name == Name) {
		return &HappyforPitty;
	}
	if (AdmirationGloating.Name == Name) {
		return &AdmirationGloating;
	}
	if (PrideShame.Name == Name) {
		return &PrideShame;
	}
	if (ConcentrationBore.Name == Name) {
		return &ConcentrationBore;
	}
	if (AngerRemorse.Name == Name) {
		return &AngerRemorse;
	}
	if (GratitudeResentment.Name == Name) {
		return &GratitudeResentment;
	}
	if (LoveHate.Name == Name) {
		return &LoveHate;
	}
	if (HopeFear.Name == Name) {
		return &HopeFear;
	}
	if (ReliefFearsConfirmed.Name == Name) {
		return &ReliefFearsConfirmed;
	}
	if (SatisfactionDisapointment.Name == Name) {
		return &SatisfactionDisapointment;
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
		const auto Factor = (Desirability + DesirabilityForOthers) / 2;
		Emotions.HappyforPitty.Amount = Factor;
		Emotions.AdmirationGloating.Amount = Factor;

		GeneratedEmotions.Add(Emotions.HappyforPitty);
		GeneratedEmotions.Add(Emotions.AdmirationGloating);
	}
	if (Praiseworthiness != 0) {
		Emotions.PrideShame.Amount = Praiseworthiness;
		Emotions.ConcentrationBore.Amount = Praiseworthiness;

		GeneratedEmotions.Add(Emotions.PrideShame);
		GeneratedEmotions.Add(Emotions.ConcentrationBore);
	}
	if (Desirability != 0 && Praiseworthiness != 0) {
		const auto Factor = (Desirability + Praiseworthiness) / 2;
		Emotions.AngerRemorse.Amount = Factor;
		Emotions.GratitudeResentment.Amount = Factor;

		GeneratedEmotions.Add(Emotions.AngerRemorse);
		GeneratedEmotions.Add(Emotions.GratitudeResentment);
	}
	if (Like != 0) {
		Emotions.JoyDistress.Amount = Like;

		GeneratedEmotions.Add(Emotions.LoveHate);
	}
	if (GoalStatus != 0 || GoalConduciveness != 0 || GoalSucessProbability != 0) {
		const auto Factor = (GoalStatus + GoalConduciveness + GoalSucessProbability) / 3;
		Emotions.HopeFear.Amount = Factor;
		Emotions.ReliefFearsConfirmed.Amount = Factor;
		Emotions.SatisfactionDisapointment.Amount = Factor;

		GeneratedEmotions.Add(Emotions.HopeFear);
		GeneratedEmotions.Add(Emotions.ReliefFearsConfirmed);
		GeneratedEmotions.Add(Emotions.SatisfactionDisapointment);
	}

	return GeneratedEmotions;
}

FFatimaGoal::FFatimaGoal(float* Variable, float SuccessValue, FString Description) :Description(Description), SuccessValue(SuccessValue), Variable(Variable) {
	if (Variable) {
		StartValue = *Variable;
	}
}
