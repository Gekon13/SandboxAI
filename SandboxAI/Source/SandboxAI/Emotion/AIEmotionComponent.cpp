// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionComponent.h"

UAIEmotionComponent::UAIEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FatimaEmotionEngine = CreateDefaultSubobject<UAIFatimaEmotionEngine>(TEXT("FATIMA"));
	PsiEmotionEngine = CreateDefaultSubobject<UAIPsiEmotionEngine>(TEXT("PSI"));
	SimplexEmotionEngine = CreateDefaultSubobject<UAISimplexEmotionEngine>(TEXT("SIMPLEX"));
	WasabiEmotionEngine = CreateDefaultSubobject<UAIWasabiEmotionEngine>(TEXT("WASABI"));

	EmotionEnginePtr = nullptr;
	EEmotionEngineModel::None;
}

void UAIEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (EmotionEngineModel != EEmotionEngineModel::None)
	{
		switch (EmotionEngineModel)
		{
		case EEmotionEngineModel::Fatima:
			{
				EmotionEnginePtr = FatimaEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Psi:
			{
				EmotionEnginePtr = PsiEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Simplex:
			{
				EmotionEnginePtr = SimplexEmotionEngine;
			}
			break;
		case EEmotionEngineModel::Wasabi:
			{
				EmotionEnginePtr = WasabiEmotionEngine;
			}
			break;
		}

		if (GetEmotionEngine() != nullptr)
		{
			GetEmotionEngine()->InitializeEmotionEngine(&EmotionKnowledge);
			GetEmotionEngine()->OnPassDecision.BindSP(TSharedRef<UAIEmotionComponent>(this), &UAIEmotionComponent::ReceivePassedDecision);
		}
	}
}


void UAIEmotionComponent::TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);

	if (TickType != ELevelTick::LEVELTICK_PauseTick) // ensure we don't tick when game is paused
	{
		if (GetEmotionEngine() != nullptr)
		{
			GetEmotionEngine()->TickEmotionEngine(DeltaSeconds);
		}
	}
}

void UAIEmotionComponent::ReceivePassedDecision(const FEmotionDecisionInfo& decisionInfo)
{
	OnDecisionMade.Broadcast(decisionInfo);
}