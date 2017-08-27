// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiBaseEmotionComponent.h"
#include "Emotion/Wasabi/AIWasabiOriginalEngineCore.h"
#include "WasabiBaseAIController.h"

AWasabiBaseAIController::AWasabiBaseAIController() : Super()
{
	WasabiEmotionComponent = CreateDefaultSubobject<UWasabiBaseEmotionComponent>(TEXT("Wasabi Emotion Component"));

	MinColor = FLinearColor::Green;
	MaxColor = FLinearColor::Red;

	bSaveWasabiStates = false;
}
void AWasabiBaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AWasabiBaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (WasabiEmotionComponent != nullptr)
	{
		float JoyDistance = WasabiEmotionComponent->GetJoyDistance();
		float DistressDistance = WasabiEmotionComponent->GetDistressDistance();

		if (JoyDistance > SMALL_NUMBER || DistressDistance > SMALL_NUMBER)
		{
			float coeficient = JoyDistance / (JoyDistance + DistressDistance);

			SetFollowSpeedCoefficient(coeficient);
			SetEmotionVisualColor(FMath::Lerp<FLinearColor>(MinColor, MaxColor, coeficient));
		}

		//FWasabiEngineStepState stepState = WasabiEmotionComponent->GetWasabiEngineCore()->GetWasabiEngineStepState();
		//WasabiStates.Add(stepState);
		
		//FWasabiEngineStepStateCGI stepStateCGI = FWasabiEngineStepStateCGI(stepState);
		//stepStateCGI.Joy = JoyDistance;
		//stepStateCGI.Distress = DistressDistance;
		//stepStateCGI.Speed = FollowSpeedCurrent;
		//stepStateCGI.DistanceCovered = TotalDistanceCovered;
		//WasabiStates.Add(stepStateCGI);
	}
}
void AWasabiBaseAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement emotionStimulusElement)
{
	//Super::HandleEmotionStimulusElement_Implementation(emotionStimulusElement); // probably never uncomment this

	switch (emotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		if (WasabiEmotionComponent != nullptr)
		{
			WasabiEmotionComponent->ReceiveImpulse(emotionStimulusElement.Power);
		}
		break;
	case EEmotionStimulusElementType::ENegative:
		if (WasabiEmotionComponent != nullptr)
		{
			WasabiEmotionComponent->ReceiveImpulse(-emotionStimulusElement.Power);
		}
		break;
	}
}
