// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiAppraisal.h"
#include "Emotion/AIEmotionKnowledge.h"
#include "Emotion/AIEmotionConstants.h"

FAIWasabiAppraisal::FAIWasabiAppraisal() :
	WasabiEngineCore(nullptr),
	Knowledge(nullptr),
	Memory(nullptr)
{
}

FAIWasabiAppraisal::FAIWasabiAppraisal(UAIWasabiBaseEngineCore* wasabiEngineCore, UAIEmotionKnowledge* knowledge, UAIEmotionKnowledge* memory) :
	WasabiEngineCore(wasabiEngineCore),
	Knowledge(knowledge),
	Memory(memory)
{
}

void FAIWasabiAppraisal::AppraiseAction(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor)
{
	//if (WasabiEngineCore != nullptr && Knowledge != nullptr)
	//{
	//	int32 informationNumber = Knowledge->Informations.Num();
	//	for (int32 informationIndex = 0; informationNumber < informationNumber; ++informationIndex)
	//	{
	//		if (Knowledge->Informations[informationIndex].DoesActorMatchTarget(targetActor))
	//		{
	//			int32 emotionDeltaNumber = Knowledge->Informations[informationIndex].EmotionDeltas.Num();
	//			for (int32 emotionDeltaIndex = 0; emotionDeltaIndex < emotionDeltaNumber; ++emotionDeltaIndex)
	//			{
	//				if (Knowledge->Informations[informationIndex].EmotionDeltas[emotionDeltaIndex].EmotionPairName == EEmotionPairName::Joy_Distress)
	//				{
	//					WasabiEngineCore->Impulse(Knowledge->Informations[informationIndex].EmotionDeltas[emotionDeltaIndex])
	//				}
	//			}
	//			//WasabiEngineCore->Impulse()
	//		}
	//	}

	//	TArray<FAIEmotionInformation> 
	//}
}