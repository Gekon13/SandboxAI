// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionVisibleInterface.h"


// Add default functionality here for any IAIEmotionVisibleInterface functions that are not pure virtual.

void IAIEmotionVisibleInterface::NotifyOnEmotionActionPerformed_Implementation(EEmotionActionName emotionActionName, AActor* sourceActor = nullptr, AActor* targetActor = nullptr)
{
	OnEmotionActionPerformed.Broadcast(emotionActionName, sourceActor, targetActor);
}