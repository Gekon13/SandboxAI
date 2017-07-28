// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEmotionKnoledge.h"

FAIEmotionKnowledge::FAIEmotionKnowledge()
{
	AvailableActionNames.Add(FString(TEXT("Roam")));
	AvailableActionNames.Add(FString(TEXT("Run")));
	AvailableActionNames.Add(FString(TEXT("Shoot")));
}