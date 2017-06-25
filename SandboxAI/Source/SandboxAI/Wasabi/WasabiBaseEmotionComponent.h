// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "WasabiBaseEmotionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOXAI_API UWasabiBaseEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWasabiBaseEmotionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wasabi", meta = (AllowPrivateAcces = "true", MakeEditWidget = "true"))
		class UWasabiEngine* WasabiEngine;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wasabi")
		float JoyDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wasabi")
		float DistressDistance;

public:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void ReceiveImpulse(float value);

	FORCEINLINE const float GetJoyDistance() const { return JoyDistance; }
	FORCEINLINE const float GetDistressDistance() const { return DistressDistance; }

	FORCEINLINE class UWasabiEngine* GetWasabiEngine() const { return WasabiEngine; }
};
