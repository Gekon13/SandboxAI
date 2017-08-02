// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "Appraisal.h"


FAppraisal::FAppraisal(float Desirability, float DesirabilityForOthers, float Praiseworthiness, float Like, float GoalStatus, float GoalConduciveness, float GoalSucessProbability)
	:Desirability(Desirability), DesirabilityForOthers(DesirabilityForOthers), Praiseworthiness(Praiseworthiness), Like(Like),
	GoalStatus(GoalStatus), GoalConduciveness(GoalConduciveness), GoalSucessProbability(GoalSucessProbability) {}

FAppraisal FAppraisal::UpdateAppraisal(FAppraisal Appraisal, float DeltaTime) {
	UpdateEmotions(&Appraisal.Desirability, DeltaTime);
	UpdateEmotions(&Appraisal.DesirabilityForOthers, DeltaTime);
	UpdateEmotions(&Appraisal.Praiseworthiness, DeltaTime);
	UpdateEmotions(&Appraisal.Like, DeltaTime);
	UpdateEmotions(&Appraisal.GoalStatus, DeltaTime);
	UpdateEmotions(&Appraisal.GoalConduciveness, DeltaTime);
	UpdateEmotions(&Appraisal.GoalSucessProbability, DeltaTime);

	return Appraisal;
}

void FAppraisal::UpdateEmotions(float* Variable, float DeltaTime) {
	*Variable *= DeltaTime * 0.1f;
}

TArray<FEmotion> FAppraisal::GenerateEmotions() {
	auto Emotions = FEmotions();
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
