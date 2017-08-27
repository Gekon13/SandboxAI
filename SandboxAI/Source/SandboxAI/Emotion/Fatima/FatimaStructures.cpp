// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "FatimaStructures.h"


FFatimaEmotion::FFatimaEmotion(EEmotionPairName Name) :Name(Name) {
	Amount = 0;
	DecayFactor = 0.01f;
	AmountAfterEvent = 0;
	TimeOfEvent = 0;
	bContinuous = false;
}

FFatimaEmotions::FFatimaEmotions() {
	JoyDistress = FFatimaEmotion(EEmotionPairName::Joy_Distress);
	HappyforPitty = FFatimaEmotion(EEmotionPairName::Happyfor_Pitty);
	AdmirationGloating = FFatimaEmotion(EEmotionPairName::Admiration_Gloating);
	PrideShame = FFatimaEmotion(EEmotionPairName::Pride_Shame);
	ConcentrationBore = FFatimaEmotion(EEmotionPairName::Concentration_Bore);
	AngerRemorse = FFatimaEmotion(EEmotionPairName::Anger_Remorse);
	GratitudeResentment = FFatimaEmotion(EEmotionPairName::Gratitude_Resentment);
	LoveHate = FFatimaEmotion(EEmotionPairName::Love_Hate);
	HopeFear = FFatimaEmotion(EEmotionPairName::Hope_Fear);
	ReliefFearsConfirmed = FFatimaEmotion(EEmotionPairName::Relief_FearsConfirmed);
	SatisfactionDisapointment = FFatimaEmotion(EEmotionPairName::Satisfaction_Disapointment);
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
