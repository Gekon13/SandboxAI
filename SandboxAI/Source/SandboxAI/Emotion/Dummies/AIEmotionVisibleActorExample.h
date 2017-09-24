// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../AIEmotionVisibleInterface.h"
#include "../Containers/AIEmotionConstants.h"
#include "AIEmotionVisibleActorExample.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UTextRenderComponent;
class UAIEmotionSightStimuliComponent;
class UGameplayComponent;

UCLASS()
class SANDBOXAI_API AAIEmotionVisibleActorExample : public AActor, public IAIEmotionVisibleInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		UAIEmotionSightStimuliComponent* SightStimuliComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		UGameplayComponent* GameplayComponent;

protected:
	FLinearColor TextInitialColor;
	FLinearColor TextTargetColor;

	FVector TextInitialRelativeLocation;
	FVector TextTargetRelativeLocation;

	/** Select any other than None for this actor to perform actions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		EEmotionActionName ActionToPerform;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float ActionTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		float ActionInterval;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotion")
		float TextFadeTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotion")
		float TextFadeLength;

	bool bTextIsFading;

public:	
	AAIEmotionVisibleActorExample();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	void ProcessActions(float DeltaSeconds);

	void SetText(const FText& newText);
	void ProcessTextRender(float DeltaSeconds);

	void UpdateTextRender(bool show, float progress = 0.0f);
};
