// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "EmotionSplineAIController.h"
#include "Emotion/AIEmotionComponent.h"

AEmotionSplineAIController::AEmotionSplineAIController() : Super()
{
	EmotionComponent = CreateDefaultSubobject<UAIEmotionComponent>(TEXT("AI Emotion Component"));

	ActionWithSpeedCoeficient = TEXT("Run");

	MinColor = FLinearColor::Green;
	MaxColor = FLinearColor::Red;

	SetCoeficient(0.5f);
}

void AEmotionSplineAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	if (EmotionComponent != nullptr)
	{
		EmotionComponent->OnDecisionMade.AddDynamic(this, &AEmotionSplineAIController::HandleDecisionMade);
	}
}
void AEmotionSplineAIController::UnPossess()
{
	Super::UnPossess();
	if (EmotionComponent != nullptr)
	{
		EmotionComponent->OnDecisionMade.RemoveDynamic(this, &AEmotionSplineAIController::HandleDecisionMade);
	}
}

void AEmotionSplineAIController::HandleDecisionMade(const FEmotionDecisionInfo& decisionInfo)
{
	//UE_LOG(LogTemp, Log, TEXT("I got Decision: %s"), *decisionInfo.ActionName);
	if (decisionInfo.ActionName.Compare(ActionWithSpeedCoeficient) == 0)
	{
		SetCoeficient(decisionInfo.ActionFValue);
	}
}

void AEmotionSplineAIController::SetCoeficient(float coeficient)
{
	Coeficient = coeficient;
	SetFollowSpeedCoefficient(Coeficient);
	
	SetEmotionVisualColor(FLinearColor::LerpUsingHSV(MinColor, MaxColor, Coeficient));
	//SetEmotionVisualColor(FMath::Lerp<FLinearColor>(MinColor, MaxColor, Coeficient));
}