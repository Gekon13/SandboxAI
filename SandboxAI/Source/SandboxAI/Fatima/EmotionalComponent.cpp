// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "EmotionalComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "ReactsToEmotions.h"
#include "TimerManager.h"


UEmotionalComponent::UEmotionalComponent() {
	PrimaryComponentTick.bCanEverTick = true;
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

	EmotionColorMin = FLinearColor::Red;
	EmotionColorMax = FLinearColor::Green;

	OnSensorUpdated.AddDynamic(this, &UEmotionalComponent::OnEventUpdated);
}

void UEmotionalComponent::AddContinuousStimulus(FEmotionStimulusFatima EmotionStimulus) {
	SetEmotionContinuous(*EmotionStimulus.Appraisal, true);
	EmotionStimuluses.Add(EmotionStimulus);
}

void UEmotionalComponent::RemoveContinuousStimulus(AActor* Instigator) {
	for (int i = 0; i < EmotionStimuluses.Num(); ++i) {
		if (EmotionStimuluses[i].Instigator == Instigator) {
			SetEmotionContinuous(*EmotionStimuluses[i].Appraisal, false);
			EmotionStimuluses.RemoveAt(i);
			break;
		}
	}
}

void UEmotionalComponent::SetEmotionContinuous(FAppraisal Appraisal, bool Continuous) {
	auto GeneratedEmotions = Appraisal.GenerateEmotions();
	for (auto AppraisalEmotion : GeneratedEmotions) {
		auto Emotion = Emotions.FindEmotionWithName(AppraisalEmotion.Name);
		if (Emotion) {
			Emotion->bContinuous = Continuous;
		}
	}
}

void UEmotionalComponent::BeginPlay() {
	Super::BeginPlay();

	auto Character = Cast<ACharacter>(GetOwner());
	if (Character) {
		MovementComponent = Character->GetCharacterMovement();
		MinMovementSpeed = MovementComponent->GetMaxSpeed() / SpeedFactor;
		MaxMovementSpeed = MovementComponent->GetMaxSpeed() + (MovementComponent->GetMaxSpeed() - MinMovementSpeed);
	}

	GetWorld()->GetTimerManager().SetTimer(ContinuousTimerHandle, this, &UEmotionalComponent::UpdateContinuousStimulus, ContinuousEmotionsInterval, true);
	GetWorld()->GetTimerManager().SetTimer(GoalsTimerHandle, this, &UEmotionalComponent::UpdateGoals, GoalsInterval, true);
}

void UEmotionalComponent::UpdateContinuousStimulus() {
	for (auto EmotionStimulus : EmotionStimuluses) {
		auto Appraisal = FAppraisal::UpdateAppraisal(*EmotionStimulus.Appraisal, ContinuousEmotionsInterval);
		OnEventUpdated(Appraisal);
	}
}

void UEmotionalComponent::UpdateGoals() {
	for (auto Goal : Goals) {
		auto GoalStatus = (*Goal.Variable - Goal.StartValue) / (Goal.SuccessValue - Goal.StartValue);
		auto Appraisal = FAppraisal::UpdateAppraisal(FAppraisal(0, 0, 0, 0, GoalStatus, 0, 0), GoalsInterval);
		OnEventUpdated(Appraisal);
	}
}

void UEmotionalComponent::OnEventUpdated(FAppraisal Appraisal) {
	auto MoodFactor = Mood * MoodRelevance / MaxMood;
	UpdateEmotions(&Appraisal, MoodFactor);
}

void UEmotionalComponent::UpdateEmotions(FAppraisal* Appraisal, float MoodFactor) {
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

void UEmotionalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, FString("Mood: ").Append(FString::SanitizeFloat(Mood)));
	GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Red, FString("JoyDistress: ").Append(FString::SanitizeFloat(Emotions.JoyDistress.Amount)));
	GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Red, FString("HappyforResentment: ").Append(FString::SanitizeFloat(Emotions.HappyforResentment.Amount)));
	GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Red, FString("GloatingPity: ").Append(FString::SanitizeFloat(Emotions.GloatingPity.Amount)));
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Red, FString("PrideShame: ").Append(FString::SanitizeFloat(Emotions.PrideShame.Amount)));
	GEngine->AddOnScreenDebugMessage(6, 1.f, FColor::Red, FString("AdmirationReproach: ").Append(FString::SanitizeFloat(Emotions.AdmirationReproach.Amount)));
	GEngine->AddOnScreenDebugMessage(7, 1.f, FColor::Red, FString("GratificationRemorse: ").Append(FString::SanitizeFloat(Emotions.GratificationRemorse.Amount)));
	GEngine->AddOnScreenDebugMessage(8, 1.f, FColor::Red, FString("GratitudeAnger: ").Append(FString::SanitizeFloat(Emotions.GratitudeAnger.Amount)));
	GEngine->AddOnScreenDebugMessage(9, 1.f, FColor::Red, FString("LoveHate: ").Append(FString::SanitizeFloat(Emotions.LoveHate.Amount)));
	GEngine->AddOnScreenDebugMessage(10, 1.f, FColor::Red, FString("HopeFear: ").Append(FString::SanitizeFloat(Emotions.HopeFear.Amount)));
	GEngine->AddOnScreenDebugMessage(11, 1.f, FColor::Red, FString("ReliefDisappointment: ").Append(FString::SanitizeFloat(Emotions.ReliefDisappointment.Amount)));
	GEngine->AddOnScreenDebugMessage(12, 1.f, FColor::Red, FString("SatisfactionFearsconfirmed: ").Append(FString::SanitizeFloat(Emotions.SatisfactionFearsconfirmed.Amount)));*/


	CalculateMood(DeltaTime);
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

void UEmotionalComponent::CalculateMood(float DeltaTime) {
	if (Mood != 0) {
		if (Mood > 0) {
			Mood = FMath::Clamp(Mood - DeltaTime * MoodDecrementAmount, 0.f, MaxMood);
		} else {
			Mood = FMath::Clamp(Mood + DeltaTime * MoodDecrementAmount, MinMood, 0.f);
		}
	}
}

void UEmotionalComponent::CalculateEmotion(FEmotion* Emotion, FEmotion* Personality) const {
	if (Emotion->Amount != Personality->Amount && !Emotion->bContinuous) {
		auto CurrentTime = GetWorld()->GetTimeSeconds() - Emotion->TimeOfEvent;
		Emotion->Amount = FMath::Clamp(Emotion->AmountAfterEvent * (FMath::Exp(-Emotion->DecayFactor * CurrentTime - Personality->Amount) + Personality->Amount), MinEmotion, MaxEmotion);
		if (FMath::Abs(Emotion->Amount - Personality->Amount) <= EmotionThreshold) {
			Emotion->Amount = Personality->Amount;
		}
	}
}

void UEmotionalComponent::UpdateActions() const {
	auto EmotionCoefficient = (Emotions.JoyDistress.Amount - MinEmotion) / (MaxEmotion - MinEmotion);
	if (MovementComponent) {
		auto CurrentSpeed = FMath::Lerp<float>(MinMovementSpeed, MaxMovementSpeed, 1 - EmotionCoefficient);
		MovementComponent->MaxWalkSpeed = CurrentSpeed;
	}
	auto Inteface = Cast<IReactsToEmotions>(GetOwner());
	if (Inteface) {
		auto Color = FMath::Lerp<FLinearColor>(EmotionColorMin, EmotionColorMax, EmotionCoefficient);
		Inteface->Execute_UpdateEmotionVisual(GetOwner(), Color);
	}
}
