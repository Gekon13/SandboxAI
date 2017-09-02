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

void UAIFatimaEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* Knowledge) {
	Super::InitializeEmotionEngine(Knowledge);

	GetOuter()->GetWorld()->GetTimerManager().SetTimer(GoalsTimerHandle, this, &UAIFatimaEmotionEngine::UpdateGoals, GoalsInterval, true);
}

void UAIFatimaEmotionEngine::TickEmotionEngine(float DeltaSeconds) {
	Super::TickEmotionEngine(DeltaSeconds);

	CalculateMood(DeltaSeconds);
	CalculateEmotion(&Emotions.JoyDistress, &Personality.JoyDistress);
	CalculateEmotion(&Emotions.HappyforPitty, &Personality.HappyforPitty);
	CalculateEmotion(&Emotions.AdmirationGloating, &Personality.AdmirationGloating);
	CalculateEmotion(&Emotions.PrideShame, &Personality.PrideShame);
	CalculateEmotion(&Emotions.ConcentrationBore, &Personality.ConcentrationBore);
	CalculateEmotion(&Emotions.AngerRemorse, &Personality.AngerRemorse);
	CalculateEmotion(&Emotions.GratitudeResentment, &Personality.GratitudeResentment);
	CalculateEmotion(&Emotions.LoveHate, &Personality.LoveHate);
	CalculateEmotion(&Emotions.HopeFear, &Personality.HopeFear);
	CalculateEmotion(&Emotions.ReliefFearsConfirmed, &Personality.ReliefFearsConfirmed);
	CalculateEmotion(&Emotions.SatisfactionDisapointment, &Personality.SatisfactionDisapointment);
	UpdateActions();
}

void UAIFatimaEmotionEngine::HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor) {
	TArray<FStringFormatArg> Arguments;
	Arguments.Add(FAIEmotionConstants::ActionNames[EmotionActionName]);
	Arguments.Add(SourceActor->GetName());
	Arguments.Add(TargetActor ? TargetActor->GetName() : "NONE");
	const auto Text = FString::Format(TEXT("Perceived action: {0}, source: {1}, target {2}"), Arguments);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Text);

	auto InformationMatchingByActions = EmotionKnowledge->Informations.FilterByPredicate([EmotionActionName, SourceActor, TargetActor](const FAIEmotionInformation& Information) {
		return Information.EmotionActionName == EmotionActionName && Information.ActionSource.DoesActorMatchTarget(SourceActor) && Information.ActionTarget.DoesActorMatchTarget(TargetActor);
	});

	for (auto& Information : InformationMatchingByActions) {
		AppraisalEmotions(Information.EmotionDeltas);
	}
}

float UAIFatimaEmotionEngine::GetEngineScale() const {
	return 1.0f;
}

void UAIFatimaEmotionEngine::DirectValencedImpulseInternal(float Value, bool bContinuous) {
	auto Appraisal = FFatimaAppraisal(Value, 0, 0, 0, 0, 0, 0);
	UpdateEmotions(&Appraisal);
}

void UAIFatimaEmotionEngine::UpdateEmotion(const float MoodFactor, const FFatimaEmotion AppraisalEmotion) {
	const auto Emotion = Emotions.FindEmotionWithName(AppraisalEmotion.Name);
	if (Emotion) {
		const auto OldValue = Emotion->Amount;
		Emotion->Amount = FMath::Clamp(Emotion->Amount + AppraisalEmotion.Amount + MoodFactor, MinEmotion, MaxEmotion);
		Emotion->AmountAfterEvent = Emotion->Amount;
		Emotion->TimeOfEvent = GetOuter()->GetWorld()->GetTimeSeconds();
		Mood = FMath::Clamp(Mood + Emotion->Amount - OldValue, MinMood, MaxMood);
	}
}

void UAIFatimaEmotionEngine::UpdateEmotions(FFatimaAppraisal* Appraisal) {
	const auto MoodFactor = Mood * MoodRelevance / MaxMood;
	auto GeneratedEmotions = Appraisal->GenerateEmotions();
	for (const auto AppraisalEmotion : GeneratedEmotions) {
		UpdateEmotion(MoodFactor, AppraisalEmotion);
	}
}

void UAIFatimaEmotionEngine::AppraisalEmotions(TArray<FAIEmotionDelta> EmotionDeltas) {
	const auto MoodFactor = Mood * MoodRelevance / MaxMood;
	for (const auto EmotionDelta : EmotionDeltas) {
		const auto AppraisalEmotion = FFatimaEmotion(EmotionDelta.EmotionPairName, EmotionDelta.EmotionPairDelta);
		UpdateEmotion(MoodFactor, AppraisalEmotion);
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
		const auto CurrentTime = GetOuter()->GetWorld()->GetTimeSeconds() - Emotion->TimeOfEvent;
		Emotion->Amount = FMath::Clamp(Emotion->AmountAfterEvent * (FMath::Exp(-Emotion->DecayFactor * CurrentTime - PersonalityEmotion->Amount) + PersonalityEmotion->Amount), MinEmotion, MaxEmotion);
		if (FMath::Abs(Emotion->Amount - PersonalityEmotion->Amount) <= EmotionThreshold) {
			Emotion->Amount = PersonalityEmotion->Amount;
		}
	}
}

void UAIFatimaEmotionEngine::UpdateActions() {
	auto EmotionCoefficient = (Emotions.JoyDistress.Amount - MinEmotion) / (MaxEmotion - MinEmotion);
	const auto CurrentSpeed = 1 - EmotionCoefficient;
	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], CurrentSpeed));
}

void UAIFatimaEmotionEngine::UpdateGoals() {
	for (const auto Goal : Goals) {
		const auto GoalStatus = (*Goal.Variable - Goal.StartValue) / (Goal.SuccessValue - Goal.StartValue);
		auto Appraisal = FFatimaAppraisal::UpdateAppraisal(FFatimaAppraisal(0, 0, 0, 0, GoalStatus, 0, 0), GoalsInterval);
		UpdateEmotions(&Appraisal);
	}
}
