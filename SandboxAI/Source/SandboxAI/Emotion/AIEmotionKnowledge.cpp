// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionKnowledge.h"

FAIEmotionKnowledge::FAIEmotionKnowledge()
{
	AvailableActionNames.Add(FString(TEXT("Faster")));
	AvailableActionNames.Add(FString(TEXT("Slower")));
}