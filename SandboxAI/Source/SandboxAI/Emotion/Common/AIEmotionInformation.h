// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SandboxAI.h"

//#ifdef TERMINATOR_API
//#include "Characters/Components/GameplayComponent.h"
//#else
//#include "MockFromTerminator/GameplayComponent.h"
//#endif

#include "MockFromTerminator/GameplayComponent.h"

#include "AIEmotionConstants.h"
#include "../AIEmotionVisibleInterface.h"
#include <initializer_list>
#include "AIEmotionInformation.generated.h"


UENUM(BlueprintType)
enum class EEmotionTargetType : uint8
{
	None = 0,
	Class = 1,
	Unit = 2,
	Team = 3,
};

/** Class used to specify target of the action percived by the emotion */
USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionTarget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> TargetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName TargetName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETeamType TeamID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionTargetType EmotionTargetType;

public:
	FORCEINLINE FAIEmotionTarget();
	FORCEINLINE FAIEmotionTarget(const FAIEmotionTarget &source);
	FORCEINLINE FAIEmotionTarget(TSubclassOf<AActor> targetClass);
	FORCEINLINE FAIEmotionTarget(TSubclassOf<AActor> targetClass, FName targetName);
	FORCEINLINE FAIEmotionTarget(ETeamType teamID);

	bool DoesActorMatchTarget(AActor* actor) const;
	static FAIEmotionTarget AsClassTarget(AActor* actor);
	static FAIEmotionTarget AsUnitTarget(AActor* actor);
};

FAIEmotionTarget::FAIEmotionTarget() : TargetClass(AActor::StaticClass()), TargetName(FName()), TeamID(ETeamType::NEUTRAL), EmotionTargetType(EEmotionTargetType::None) {}
FAIEmotionTarget::FAIEmotionTarget(const FAIEmotionTarget &source) : TargetClass(source.TargetClass), TargetName(source.TargetName), TeamID(source.TeamID), EmotionTargetType(source.EmotionTargetType) {}
FAIEmotionTarget::FAIEmotionTarget(TSubclassOf<AActor> targetClass) : TargetClass(targetClass), TargetName(FName()), TeamID(ETeamType::NEUTRAL), EmotionTargetType(EEmotionTargetType::Class) {}
FAIEmotionTarget::FAIEmotionTarget(TSubclassOf<AActor> targetClass, FName targetName) : TargetClass(targetClass), TargetName(targetName), TeamID(ETeamType::NEUTRAL), EmotionTargetType(EEmotionTargetType::Unit) {}
FAIEmotionTarget::FAIEmotionTarget(ETeamType teamID) : TargetClass(AActor::StaticClass()), TargetName(FName()), TeamID(teamID), EmotionTargetType(EEmotionTargetType::Team) {}

/** Structure used to specify in emotion pair when particular action occurs */
USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionDelta
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionPairName EmotionPairName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EmotionPairDelta;

public:
	FORCEINLINE FAIEmotionDelta();
	FORCEINLINE FAIEmotionDelta(const FAIEmotionDelta& source);
	FORCEINLINE FAIEmotionDelta(EEmotionPairName emotionPairName, float emotionPairDelta = 0.0f);

};

FAIEmotionDelta::FAIEmotionDelta() : EmotionPairName(EEmotionPairName::None), EmotionPairDelta(0.0f) {}
FAIEmotionDelta::FAIEmotionDelta(const FAIEmotionDelta& source) : EmotionPairName(source.EmotionPairName), EmotionPairDelta(source.EmotionPairDelta) {}
FAIEmotionDelta::FAIEmotionDelta(EEmotionPairName emotionPairName, float emotionPairDelta) : EmotionPairName(emotionPairName), EmotionPairDelta(emotionPairDelta) {}

USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionInformation
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionActionName EmotionActionName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAIEmotionTarget ActionSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAIEmotionTarget ActionTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FAIEmotionDelta> EmotionDeltas;

public:
	FORCEINLINE FAIEmotionInformation();

	FORCEINLINE FAIEmotionInformation(const FAIEmotionInformation& source);

	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, const TArray<FAIEmotionDelta>& emotionDeltas);
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, const std::initializer_list<FAIEmotionDelta>& emotionDeltas);

	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource ,const TArray<FAIEmotionDelta>& emotionDeltas);
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const std::initializer_list<FAIEmotionDelta>& emotionDeltas);
	
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, const TArray<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget);
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, const std::initializer_list<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget);
	
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const TArray<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget);
	FORCEINLINE FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const std::initializer_list<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget);
};

FAIEmotionInformation::FAIEmotionInformation() 
	: EmotionActionName(EEmotionActionName::None), ActionSource(FAIEmotionTarget()), ActionTarget(FAIEmotionTarget()) {}

FAIEmotionInformation::FAIEmotionInformation(const FAIEmotionInformation& source) 
	: EmotionActionName(source.EmotionActionName), ActionSource(source.ActionSource), ActionTarget(source.ActionTarget), EmotionDeltas(source.EmotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, const TArray<FAIEmotionDelta>& emotionDeltas) 
	: EmotionActionName(emotionActionName), ActionSource(FAIEmotionTarget()), ActionTarget(FAIEmotionTarget()), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, const std::initializer_list<FAIEmotionDelta>& emotionDeltas)
	: EmotionActionName(emotionActionName), ActionSource(FAIEmotionTarget()), ActionTarget(FAIEmotionTarget()), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const TArray<FAIEmotionDelta>& emotionDeltas)
	: EmotionActionName(emotionActionName), ActionSource(actionSource), ActionTarget(FAIEmotionTarget()), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const std::initializer_list<FAIEmotionDelta>& emotionDeltas)
	: EmotionActionName(emotionActionName), ActionSource(actionSource), ActionTarget(FAIEmotionTarget()), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, const TArray<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget)
	: EmotionActionName(emotionActionName), ActionSource(FAIEmotionTarget()), ActionTarget(actionTarget), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, const std::initializer_list<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget)
	: EmotionActionName(emotionActionName), ActionSource(FAIEmotionTarget()), ActionTarget(actionTarget), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const TArray<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget)
	: EmotionActionName(emotionActionName), ActionSource(actionSource), ActionTarget(actionTarget), EmotionDeltas(emotionDeltas) {}

FAIEmotionInformation::FAIEmotionInformation(EEmotionActionName emotionActionName, FAIEmotionTarget actionSource, const std::initializer_list<FAIEmotionDelta>& emotionDeltas, FAIEmotionTarget actionTarget)
	: EmotionActionName(emotionActionName), ActionSource(actionSource), ActionTarget(actionTarget), EmotionDeltas(emotionDeltas) {}