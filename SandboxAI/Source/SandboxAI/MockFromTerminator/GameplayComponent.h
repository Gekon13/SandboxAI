// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayComponent.generated.h"


UENUM(BlueprintType)
enum class ETeamType : uint8
{
	FRIENDLY = 0,
	ENEMY,
	NEUTRAL
};

UCLASS()
class SANDBOXAI_API UGameplayComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UGameplayComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category = "Team")
	ETeamType TeamID;
	
};