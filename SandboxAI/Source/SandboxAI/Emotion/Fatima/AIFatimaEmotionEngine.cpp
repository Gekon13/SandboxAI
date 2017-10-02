// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIFatimaEmotionEngine.h"

#define SAVE_LOG false

UAIFatimaEmotionEngine::UAIFatimaEmotionEngine() {
	Mood = 0;
	MinMood = -11.f;
	MaxMood = 11.f;
	MinEmotion = -1.f;
	MaxEmotion = 1.f;

	PersonalityRelevance = 0.1f;
	MoodDecrementAmount = 0.005f;
	MoodRelevance = 0.1f;
	GoalsInterval = 0.5f;
}

void UAIFatimaEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* Knowledge) {
	Super::InitializeEmotionEngine(Knowledge);

	GetOuter()->GetWorld()->GetTimerManager().SetTimer(GoalsTimerHandle, this, &UAIFatimaEmotionEngine::UpdateGoals, GoalsInterval, true);
}

void UAIFatimaEmotionEngine::TickEmotionEngine(float DeltaSeconds) {
	Super::TickEmotionEngine(DeltaSeconds);

	CalculateMood(DeltaSeconds);
	CalculateEmotion(&CurrentEmotions.JoyDistress, &Personality.JoyDistress);
	CalculateEmotion(&CurrentEmotions.HappyforPitty, &Personality.HappyforPitty);
	CalculateEmotion(&CurrentEmotions.AdmirationGloating, &Personality.AdmirationGloating);
	CalculateEmotion(&CurrentEmotions.PrideShame, &Personality.PrideShame);
	CalculateEmotion(&CurrentEmotions.ConcentrationBore, &Personality.ConcentrationBore);
	CalculateEmotion(&CurrentEmotions.AngerRemorse, &Personality.AngerRemorse);
	CalculateEmotion(&CurrentEmotions.GratitudeResentment, &Personality.GratitudeResentment);
	CalculateEmotion(&CurrentEmotions.LoveHate, &Personality.LoveHate);
	CalculateEmotion(&CurrentEmotions.HopeFear, &Personality.HopeFear);
	CalculateEmotion(&CurrentEmotions.ReliefFearsConfirmed, &Personality.ReliefFearsConfirmed);
	CalculateEmotion(&CurrentEmotions.SatisfactionDisapointment, &Personality.SatisfactionDisapointment);
	UpdateActions();
}

void UAIFatimaEmotionEngine::HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor) {
	/*TArray<FStringFormatArg> Arguments;
	Arguments.Add(FAIEmotionConstants::ActionNames[EmotionActionName]);
	Arguments.Add(SourceActor->GetName());
	Arguments.Add(TargetActor ? TargetActor->GetName() : "NONE");
	const auto Text = FString::Format(TEXT("Perceived action: {0}, source: {1}, target {2}"), Arguments);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Text);*/

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
	const auto Emotion = CurrentEmotions.FindEmotionWithName(AppraisalEmotion.Name);
	const auto PersonalityEmotion = Personality.FindEmotionWithName(AppraisalEmotion.Name);
	if (Emotion && PersonalityEmotion) {
		const auto OldValue = Emotion->Amount;
		Emotion->Amount = FMath::Clamp(Emotion->Amount + AppraisalEmotion.Amount + MoodFactor + PersonalityEmotion->Amount * PersonalityRelevance, MinEmotion, MaxEmotion);
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
		Emotion->Amount = FMath::Clamp(Emotion->AmountAfterEvent * (FMath::Exp(-PersonalityEmotion->DecayFactor * CurrentTime - PersonalityEmotion->Amount) + PersonalityEmotion->Amount), MinEmotion, MaxEmotion);
		if (FMath::Abs(Emotion->Amount - PersonalityEmotion->Amount) <= PersonalityEmotion->Threshold) {
			Emotion->Amount = PersonalityEmotion->Amount;
		}
	}
}

void UAIFatimaEmotionEngine::UpdateActions() {
	const auto EmotionDiff = MaxEmotion - MinEmotion;
	const auto EmotionCoefficient = (CurrentEmotions.JoyDistress.Amount - MinEmotion) / EmotionDiff;
	const auto CurrentSpeed = 1 - EmotionCoefficient;
	/*const auto EmotionCoefficientLove = (CurrentEmotions.LoveHate.Amount - MinEmotion) / EmotionDiff;
	const auto EmotionCoefficientHope = (CurrentEmotions.HopeFear.Amount - MinEmotion) / EmotionDiff;
	const auto CurrentSpeed = (1 - EmotionCoefficient + 1 - EmotionCoefficientLove + 1 - EmotionCoefficientHope) / 3;*/
	if (SAVE_LOG) {
		SaveLogs(CurrentSpeed, "D:/TestSave");
	}

	MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], CurrentSpeed));
}

void UAIFatimaEmotionEngine::SaveLogs(const float CurrentSpeed, const FString SaveDirectory) const {
	const auto Speed = FMath::Lerp<float>(300.f, 900.f, CurrentSpeed);
	const auto FileName = FString(GetOuter()->GetOuter()->GetName() + "_t6n.csv"),
		TextToSave = FString::SanitizeFloat(Speed).Append(FString(";\r\n"));

	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory)) {
		const auto AbsoluteFilePath = SaveDirectory + "/" + FileName;
		FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
	}
}

void UAIFatimaEmotionEngine::UpdateGoals() {
	for (const auto Goal : Goals) {
		const auto GoalStatus = (*Goal.Variable - Goal.StartValue) / (Goal.SuccessValue - Goal.StartValue);
		auto Appraisal = FFatimaAppraisal::UpdateAppraisal(FFatimaAppraisal(0, 0, 0, 0, GoalStatus, 0, 0), GoalsInterval);
		UpdateEmotions(&Appraisal);
	}
}
