// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perception/AISense_Sight.h"

#include "Utility/AIEmotionSightStimuliComponent.h"
#include "Emotion/AIEmotionConstants.h"
#include "AIEmotionDummyInterface.h"

#include "AIEmotionDummyActor.generated.h"

class UAIPerceptionStimuliSourceComponent;

/** Make sure to setup AIPerceptionStimuliSourceComponent since it  has field with acces from blueprints only */
UCLASS()
class SANDBOXAI_API AAIEmotionDummyActor : public AActor, public IAIEmotionDummyInterface
{
	GENERATED_BODY()
	
public: // members

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Actor")
		UAIEmotionSightStimuliComponent* SightStimuliComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		EEmotionSimpleValency Valency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion")
		bool bContinuous;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dummy | Emotion", meta = (ClampMin = 0.0, ClampMax = 1.0, UIMin = 0.0, UIMax = 1.0))
		float Value;

public:	// methods
	AAIEmotionDummyActor();

	virtual EEmotionSimpleValency GetValency_Implementation() override;
	virtual bool IsContinuous_Implementation() override;
	virtual float GetValue_Implementation() override;
};

