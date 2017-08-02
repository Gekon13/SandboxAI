// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "Appraisal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "EmotionStimulusFatima.generated.h"

USTRUCT()
struct FEmotionStimulusFatima
{
	GENERATED_BODY()

public:
	FEmotionStimulusFatima() : FEmotionStimulusFatima(nullptr, nullptr, nullptr) {}
	FEmotionStimulusFatima(FAppraisal* Appraisal, AActor* Instigator, FAIStimulus* Stimulus);

	FAppraisal* Appraisal;
	AActor* Instigator;
	FAIStimulus* Stimulus;
};
