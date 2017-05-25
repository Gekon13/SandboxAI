// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexAIController.h"
#include "Simplex/SimplexEmotionComponent.h"

ASimplexAIController::ASimplexAIController() : Super(), SimplexEmotionComponent(nullptr)
{
	SimplexEmotionComponent = CreateDefaultSubobject<USimplexEmotionComponent>("EmotionComponent");
}

void ASimplexAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
}

void ASimplexAIController::UnPossess()
{
	Super::UnPossess();
	SimplexEmotionComponent = nullptr;
}

void ASimplexAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateEmotionalStateConsequences();
}

void ASimplexAIController::UpdateEmotionalStateConsequences()
{
	if(SimplexEmotionComponent)
	{
		const FSimplexPADPoint& NeutralState = SimplexEmotionComponent->GetNeutralEmotionalState();
		const FSimplexPADPoint& CurrentEmotionalState = SimplexEmotionComponent->GetCurrentEmotionalState();

		const float DistanceFromPureJoy = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Joy);
		const float DistanceFromPureDistress = FSimplexPADPoint::Dist(CurrentEmotionalState, FSimplexPADPoint::Distress);

		float JoyDistress = FMath::Clamp(DistanceFromPureDistress - DistanceFromPureJoy, -1.0f, 1.0f);

		float Value = 0.5f * (-JoyDistress + 1.0f);
		FString OwnerName = GetPawn()->GetName();
		GEngine->AddOnScreenDebugMessage(-1, GetWorld()->GetDeltaSeconds(), FColor::Yellow, OwnerName.Append(FString::Printf(TEXT(", Speed coeficcient:%.4f"), Value)));
		SetFollowSpeedCoefficient(Value);
		SetEmotionVisualColor(FMath::Lerp<FLinearColor>(FLinearColor::Green, FLinearColor::Red, Value));
	}
}

void ASimplexAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement)
{
	if(SimplexEmotionComponent)
	{
		SimplexEmotionComponent->HandleEmotionStimulusElement(EmotionStimulusElement);
	}
}