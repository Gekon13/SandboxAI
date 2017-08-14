// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "AIEmotionConstants.generated.h"

/*
List of emotion pairs:
Emotions	gestures
joy	distress
happyfor	pity
pride	shame
admiration	gloating
gratitude	resentment
anger	remorse
love	hate
hope	fear
relief	fears - confirmed
satisfaction	disapointment
concentration	bore
*/

#define PROJECT_API SANDBOXAI_API

UENUM(BlueprintType)
enum class EEmotionName : uint8
{
	None = 0 UMETA(DisplayName = "None"),

	Joy = 2 UMETA(DisplayName = "Joy"),
	Distress = 3 UMETA(DisplayName = "Distress"),

	Happyfor = 4 UMETA(DisplayName = "Happyfor"),
	Pitty = 5 UMETA(DisplayName = "Pitty"),

	Pride = 6 UMETA(DisplayName = "Pride"),
	Shame = 7 UMETA(DisplayName = "Shame"),

	Admiration = 8 UMETA(DisplayName = "Admiration"),
	Gloating = 9 UMETA(DisplayName = "Gloating"),

	Gratitude = 10 UMETA(DisplayName = "Gratitude"),
	Resentment = 11 UMETA(DisplayName = "Resentment"),

	Anger = 12 UMETA(DisplayName = "Anger"),
	Remorse = 13 UMETA(DisplayName = "Remorse"),

	Love = 14 UMETA(DisplayName = "Love"),
	Hate = 15 UMETA(DisplayName = "Hate"),

	Hope = 16 UMETA(DisplayName = "Hope"),
	Fear = 17 UMETA(DisplayName = "Fear"),

	Relief = 18 UMETA(DisplayName = "Relief"),
	FearsConfirmed = 19 UMETA(DisplayName = "Fears Confirmed"),

	Satisfaction = 20 UMETA(DisplayName = "Satisfaction"),
	Disapointment = 21 UMETA(DisplayName = "Disapointment"),

	Concentration = 22 UMETA(DisplayName = "Concentration"),
	Bore = 23 UMETA(DisplayName = "Bore"),
};

UENUM(BlueprintType)
enum class EEmotionPairName : uint8
{
	None = 0 UMETA(DisplayName = "None"),

	Joy_Distress				UMETA(DisplayName = "Joy-Distress"),

	Happyfor_Pitty				UMETA(DisplayName = "Happyfor-Pitty"),

	Pride_Shame					UMETA(DisplayName = "Pride-Shame"),

	Admiration_Gloating			UMETA(DisplayName = "Admiration-Gloating"),

	Gratitude_Resentment		UMETA(DisplayName = "Gratitude-Resentment"),

	Anger_Remorse				UMETA(DisplayName = "Anger-Remorse"),

	Love_Hate					UMETA(DisplayName = "Love-Hate"),

	Hope_Fear					UMETA(DisplayName = "Hope-Fear"),

	Relief_FearsConfirmed		UMETA(DisplayName = "Relief-FearsConfirmed"),

	Satisfaction_Disapointment	UMETA(DisplayName = "Satisfaction-Disapointment"),

	Concentration_Bore			UMETA(DisplayName = "Concentration-Bore"),
};

UENUM(BlueprintType)
enum class EEmotionEngineModel : uint8
{
	None = 0 UMETA(DisplayName = "No model choosen"),
	Fatima = 1 UMETA(DisplayName = "FATIMA"),
	Psi = 2 UMETA(DisplayName = "PSI"),
	Simplex = 3 UMETA(DisplayName = "SIMPLEX"),
	Wasabi = 4 UMETA(DisplayName = "WASABI"),
};

UENUM(BlueprintType)
enum class EEmotionSimpleValency : uint8
{
	Positive = 0 UMETA(DisplayName = "Positive"),
	Negative = 1 UMETA(DisplayName = "Negative"),
};

UENUM(BlueprintType)
enum class EEmotionActionName : uint8
{
	None = 0,
	WalkTowards				UMETA(DisplayName = "Walk towards"),
	RunTowards				UMETA(DisplayName = "Run towards"),
	WalkAway				UMETA(DisplayName = "Walk away"),
	RunAway					UMETA(DisplayName = "Run away"),
	See						UMETA(DisplayName = "See"),
	JoyfulGesture			UMETA(DisplayName = "Joyful Gesture"),
	DistressfulGesture		UMETA(DisplayName = "Distressful Gesture"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEmotionActionPerformed, EEmotionActionName, EmotionActionName, AActor*, sourceActor, AActor*, targetActor);

USTRUCT(BlueprintType)
struct PROJECT_API FAIEmotionConstants
{
	GENERATED_BODY()

public:
	
	/** For use with logging and general utility */
	static TMap<EEmotionName, FString> EmotionNames;

private:

	static TMap<EEmotionName, FString> BuildEmotionNamesMap();
};