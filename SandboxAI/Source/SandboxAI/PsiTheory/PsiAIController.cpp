// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "PsiAIController.h"

APsiAIController::APsiAIController() : Super(), PsiEmotionsComponent(nullptr), PsiDrives(FPsiDrives()), PsiMotivations(FPsiMotivations()), PsiGoal(FPsiGoal())
{

}

void APsiAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	if (InPawn != nullptr)
	{
		PsiEmotionsComponent = Cast<UPsiEmotions>(InPawn->GetComponentByClass(UPsiEmotions::StaticClass()));
	}
}

void APsiAIController::UnPossess()
{
	Super::UnPossess();
	PsiEmotionsComponent = nullptr;
}

void APsiAIController::Tick(float DeltaSeconds)
{
	ProcessPsiTheory();
	SetEmotionVisualColor(FMath::Lerp<FLinearColor>(FLinearColor::Green, FLinearColor::Red, PsiEmotionsComponent->Emotions[0].Value));
}

void APsiAIController::ProcessPsiTheory()
{
	PsiMotivations.Motivations = PsiDrives.GenerateMotivations();
	PsiGoal = PsiMotivations.GenerateGoal();

	switch (PsiGoal.Type)
	{
	case EPsiDrive::ECuriosity:
		if (PsiEmotionsComponent->Emotions[0].Value > 0.0f)
			MoveFaster(0.5f * (PsiGoal.Value + 1.f) * PsiEmotionsComponent->Emotions[0].Value);
		else
			MoveFaster(0.5f * (PsiGoal.Value + 1.f) * PsiEmotionsComponent->Emotions[0].Value);
		break;
	case EPsiDrive::ESafety:
		if (PsiEmotionsComponent->Emotions[0].Value > 0.0f)
			MoveFaster(0.5f * (PsiGoal.Value + 1.f) * PsiEmotionsComponent->Emotions[0].Value);
		else
			MoveFaster(0.5f * (PsiGoal.Value + 1.f) * PsiEmotionsComponent->Emotions[0].Value);
		break;
	}
}

void APsiAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement)
{
	if (PsiEmotionsComponent != nullptr)
	{
		PsiEmotionsComponent->ProcessEmotionStimulusElement(EmotionStimulusElement);
	}

	switch (EmotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		PsiDrives.Drives[0].Value = FMath::Clamp((PsiDrives.Drives[0].Value - (EmotionStimulusElement.Power / 100.f) * 0.8f), 0.0f, 1.0f);
		PsiDrives.Drives[1].Value = FMath::Clamp((PsiDrives.Drives[1].Value + (EmotionStimulusElement.Power / 100.f) * 0.8f), 0.0f, 1.0f);
		break;
	case EEmotionStimulusElementType::ENegative:
		PsiDrives.Drives[0].Value = FMath::Clamp((PsiDrives.Drives[0].Value + (EmotionStimulusElement.Power / 100.f) * 0.8f), 0.0f, 1.0f);
		PsiDrives.Drives[1].Value = FMath::Clamp((PsiDrives.Drives[0].Value - (EmotionStimulusElement.Power / 100.f) * 0.8f), 0.0f, 1.0f);
		break;
	}
}

void APsiAIController::MoveSlower(float value)
{
	SetFollowSpeedCoefficient(value);
}

void APsiAIController::MoveFaster(float value)
{
	SetFollowSpeedCoefficient(value);
}
