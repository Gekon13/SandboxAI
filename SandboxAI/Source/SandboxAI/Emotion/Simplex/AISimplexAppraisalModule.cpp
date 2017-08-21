// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexAppraisalModule.h"
#include "Emotion/AIEmotionKnowledge.h"

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForConsequences(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* TargetPawn = Cast<APawn>(TargetActor);
	if(!TargetPawn)
	{
		//It's not agent/character so there are no consequences for agents
		return FSimplexPADPoint();
	}

	if(TargetPawn == Owner)
	{
		//Consequences for self
	}
	else
	{
		//Consequences for others
	}

	return FSimplexPADPoint();
}

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForActions(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* SourcePawn = Cast<APawn>(SourceActor);
	if(!SourcePawn)
	{
		//It's not agent/character so there are no actions performed by any agent to be considered
		return FSimplexPADPoint();
	}

	if(SourcePawn == Owner)
	{
		//Actions performed by self
	}
	else
	{
		//Actions performed by others
	}

	return FSimplexPADPoint();
}

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForObjects(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* SourcePawn = Cast<APawn>(SourceActor);
	APawn* TargetPawn = Cast<APawn>(TargetActor);
	if(SourcePawn && TargetPawn)
	{
		//Both actors are pawn so there was no non-agent object performing action
		return FSimplexPADPoint();
	}

	if(SourcePawn)
	{
		//Object is the target of an action
	}
	else
	{
		//Object is the source of an action
	}

	return FSimplexPADPoint();
}

TArray<FSimplexPADPoint> UAISimplexAppraisalModule::DoAppraisal(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	TArray<FSimplexPADPoint> GeneratedEmotions;
	GeneratedEmotions.Add(Internal_DoAppraisalForConsequences(EmotionActionName, SourceActor, TargetActor));
	GeneratedEmotions.Add(Internal_DoAppraisalForActions(EmotionActionName, SourceActor, TargetActor));
	GeneratedEmotions.Add(Internal_DoAppraisalForObjects(EmotionActionName, SourceActor, TargetActor));
	return GeneratedEmotions;
}
