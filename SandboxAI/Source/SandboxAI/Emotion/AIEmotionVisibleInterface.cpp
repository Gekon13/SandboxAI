// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionVisibleInterface.h"


void IAIEmotionVisibleInterface::RequestSeeAction(AActor* sourceActor)
{
	AActor* emotionVisibleActor = Cast<AActor>(this);
	if (emotionVisibleActor != nullptr)
	{
		Execute_NotifyOnEmotionActionPerformed(emotionVisibleActor, EEmotionActionName::See, sourceActor, emotionVisibleActor);
	}
}
void IAIEmotionVisibleInterface::RequestUnSeeAction(AActor* sourceActor)
{
	AActor* emotionVisibleActor = Cast<AActor>(this);
	if (emotionVisibleActor != nullptr)
	{
		Execute_NotifyOnEmotionActionPerformed(emotionVisibleActor, EEmotionActionName::UnSee, sourceActor, emotionVisibleActor);
	}
}

void IAIEmotionVisibleInterface::NotifyOnEmotionActionPerformed_Implementation(EEmotionActionName emotionActionName, AActor* sourceActor, AActor* targetActor)
{
	OnEmotionActionPerformed.Broadcast(emotionActionName, sourceActor, targetActor);
}

