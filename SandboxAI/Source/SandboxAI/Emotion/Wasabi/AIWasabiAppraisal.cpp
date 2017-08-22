// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiAppraisal.h"
#include "Emotion/AIEmotionKnowledge.h"
#include "Emotion/AIEmotionConstants.h"
#include "Emotion/Wasabi/AIWasabiBaseEngineCore.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"

FAIWasabiAppraisal::FAIWasabiAppraisal() :
	WasabiEngineCore(nullptr),
	Knowledge(nullptr),
	Memory(nullptr)
{
}

void FAIWasabiAppraisal::Initialize(UAIWasabiBaseEngineCore* wasabiEngineCore, UAIEmotionKnowledge* knowledge, UAIEmotionKnowledge* memory)
{
	WasabiEngineCore = wasabiEngineCore;
	Knowledge = knowledge;
	Memory = memory;
}

void FAIWasabiAppraisal::AppraiseAction(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor)
{
	if (WasabiEngineCore != nullptr && Knowledge != nullptr)
	{
		TArray<FAIEmotionInformation> InformationMatchingByActions = Knowledge->Informations.FilterByPredicate(
			[EmotionActionName, sourceActor, targetActor]
			(const FAIEmotionInformation& information) 
			{ 
				return (information.EmotionActionName == EmotionActionName) && (information.ActionSource.DoesActorMatchTarget(sourceActor)) && (information.ActionTarget.DoesActorMatchTarget(targetActor)); 
			}
		);

		int32 matchingInformationNumber = InformationMatchingByActions.Num();
		if (matchingInformationNumber > 0)
		{
			for (int32 matchingInformationIndex = 0; matchingInformationIndex < matchingInformationNumber; ++matchingInformationIndex)
			{
				int32 emotionDeltaNumber = InformationMatchingByActions[matchingInformationIndex].EmotionDeltas.Num();
				for (int32 emotionDeltaIndex = 0; emotionDeltaIndex < emotionDeltaNumber; ++emotionDeltaIndex)
				{
					// wasabi defines action action appraisal only as positive or negative with rational value
					// it's all just floats
					// since all emotion pairs are set positive-negative
					// and all knowledge is based on these pairs
					// get value of pair and "make impulse"

					float impulseValue = InformationMatchingByActions[matchingInformationIndex].EmotionDeltas[emotionDeltaIndex].EmotionPairDelta;

					WasabiEngineCore->Impulse(impulseValue);
				}
			}
		}
	}
}