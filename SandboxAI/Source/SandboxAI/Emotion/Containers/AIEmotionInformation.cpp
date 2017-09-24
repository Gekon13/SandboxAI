// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIEmotionInformation.h"
#include "GameFramework/Actor.h"

bool FAIEmotionTarget::DoesActorMatchTarget(AActor* actor) const
{
	switch (EmotionTargetType)
	{
	case EEmotionTargetType::None:
		{
			return true; // if no target for emotion is specified action should match as one not requiring target
		}
		break;
	case EEmotionTargetType::Class:
		{
			return actor != nullptr && actor->IsA(TargetClass);
		}
		break;
	case EEmotionTargetType::Unit:
		{
			return actor != nullptr && actor->IsA(TargetClass) && actor->GetFName().IsEqual(TargetName, ENameCase::IgnoreCase);
		}
		break;
	case EEmotionTargetType::Team:
		{
			if (actor != nullptr)
			{
				UGameplayComponent* gameplayComponent = actor->FindComponentByClass<UGameplayComponent>();
				return gameplayComponent != nullptr && gameplayComponent->TeamID == TeamID;
			}
			else 
			{
				return false;
			}
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