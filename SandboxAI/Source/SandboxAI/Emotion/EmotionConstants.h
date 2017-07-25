// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

UENUM(BlueprintType)
enum class EWasabiEmotionPrimary : uint8
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