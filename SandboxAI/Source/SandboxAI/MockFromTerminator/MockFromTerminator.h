// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayComponent.h"

template<typename ComponentClass>
ComponentClass* FindComponent(const AActor* Actor, const FName& Name = NAME_None)
{
	if (Name != NAME_None)
	{
		TArray<UActorComponent*> Components = Actor->GetComponentsByClass(ComponentClass::StaticClass());
		for (TArray< UActorComponent* >::TConstIterator It(Components); It; ++It)
		{
			if ((*It)->GetName() == Name.ToString())
			{
				return Cast<ComponentClass>(*It);
			}
		}
	}
	ComponentClass* Component = Actor->FindComponentByClass<ComponentClass>();
	return Component;
}