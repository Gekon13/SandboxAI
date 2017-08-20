// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "AIEmotionVisibleActorExample.h"

AAIEmotionVisibleActorExample::AAIEmotionVisibleActorExample()
{
	PrimaryActorTick.bCanEverTick = true;

	ActionToPerform = EEmotionActionName::None;
	ActionTimer = 0.0f;
	ActionInterval = 0.5f;

	TextInitialColor = FLinearColor::White;
	TextTargetColor = FLinearColor::White.CopyWithNewOpacity(0.0f);

	TextInitialRelativeLocation = FVector(0.0f, 0.0f, 200.0f);
	TextTargetRelativeLocation = FVector(0.0f, 0.0f, 400.0f);

	TextFadeTimer = 0.0f;;
	TextFadeLength = 1.0f;

	bTextIsFading;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene root component"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh components"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text render component"));
	TextRenderComponent->SetupAttachment(RootComponent);
	TextRenderComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	TextRenderComponent->SetRelativeLocation(TextInitialRelativeLocation);
	TextRenderComponent->SetHiddenInGame(true);

	SightStimuliComponent = CreateDefaultSubobject<UAIEmotionSightStimuliComponent>(TEXT("AIEmotion Sight Stimuli Component"));
}

void AAIEmotionVisibleActorExample::BeginPlay()
{
	Super::BeginPlay();

	if (TextRenderComponent != nullptr)
	{
		TextInitialColor = FLinearColor( TextRenderComponent->TextRenderColor );
		TextTargetColor = TextInitialColor.CopyWithNewOpacity(0.0f);
	}
}

void AAIEmotionVisibleActorExample::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ProcessActions(DeltaSeconds);

	ProcessTextRender(DeltaSeconds);
}

void AAIEmotionVisibleActorExample::ProcessActions(float DeltaSeconds)
{
	if (ActionToPerform != EEmotionActionName::None)
	{
		ActionTimer += DeltaSeconds;
		if (ActionTimer > ActionInterval)
		{
			ActionTimer -= ActionInterval;

			Execute_NotifyOnEmotionActionPerformed(this, ActionToPerform, this, nullptr);
			SetText(FText::FromString(FAIEmotionConstants::ActionNames[ActionToPerform]));
		}
	}
}

void AAIEmotionVisibleActorExample::SetText(const FText& newText)
{
	if (TextRenderComponent != nullptr)
	{
		TextRenderComponent->SetText(newText);
		
		TextFadeTimer = 0.0f;
		bTextIsFading = true;
	}
}
void AAIEmotionVisibleActorExample::ProcessTextRender(float DeltaSeconds)
{
	if (bTextIsFading)
	{
		TextFadeTimer += DeltaSeconds;
		if (TextFadeTimer > TextFadeLength)
		{
			bTextIsFading = false;
			UpdateTextRender(false);
		}
		else
		{
			float progres = FMath::Clamp(TextFadeTimer / TextFadeLength, 0.0f, 1.0f);
			UpdateTextRender(true, progres);
		}
	}
}

void AAIEmotionVisibleActorExample::UpdateTextRender(bool show, float progress)
{
	if (TextRenderComponent != nullptr)
	{
		TextRenderComponent->SetHiddenInGame(!show);
		if (show)
		{
			FLinearColor color = FLinearColor::LerpUsingHSV(TextInitialColor, TextTargetColor, progress);
			TextRenderComponent->SetTextRenderColor(color.ToFColor(false)); // false because quality is not the goal : >

			FVector location = FMath::Lerp(TextInitialRelativeLocation, TextTargetRelativeLocation, progress);
			TextRenderComponent->SetRelativeLocation(location);
		}
	}
}