// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionVisibleInterface.h"

void IAIEmotionVisibleInterface::NotifyOnEmotionActionPerformed_Implementation(EEmotionActionName emotionActionName, AActor* sourceActor, AActor* targetActor)
{
	OnEmotionActionPerformed.Broadcast(emotionActionName, sourceActor, targetActor);
}

