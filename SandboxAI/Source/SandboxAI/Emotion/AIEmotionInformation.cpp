// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionInformation.h"
#include "GameFramework/Actor.h"

bool FAIEmotionTarget::DoesActorMatchTarget(AActor* actor)
{
	switch (EmotionTargetType)
	{
	case EEmotionTargetType::None:
		{
			return false;
		}
		break;
	case EEmotionTargetType::Class:
		{
			return actor->IsA(TargetClass);
		}
		break;
	case EEmotionTargetType::Unit:
		{
			return actor->IsA(TargetClass) && actor->GetFName().IsEqual(TargetName, ENameCase::IgnoreCase);
		}
		break;
	default:
		return false;
		break;
	}
}

FAIEmotionTarget FAIEmotionTarget::AsClassTarget(AActor* actor)
{
	if (actor != nullptr)
	{
		return FAIEmotionTarget(actor->StaticClass());
	}
	else 
	{
		return FAIEmotionTarget();
	}
}
FAIEmotionTarget FAIEmotionTarget::AsUnitTarget(AActor* actor)
{
	if (actor != nullptr)
	{
		return FAIEmotionTarget(actor->StaticClass(), actor->GetFName());
	}
	else
	{
		return FAIEmotionTarget();
	}
}