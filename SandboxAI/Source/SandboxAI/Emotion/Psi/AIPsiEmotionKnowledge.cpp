// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIPsiEmotionKnowledge.h"


UAIPsiEmotionKnowledge::UAIPsiEmotionKnowledge()/* : UAIEmotionKnowledge()*/
{
	Actions.Add(FPsiKnowledge(EPsiDrive::ESafety, FString(TEXT("Run"))));
}

