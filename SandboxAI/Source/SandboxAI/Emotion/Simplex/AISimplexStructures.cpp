// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexStructures.h"

//PAD values from "ALMA – A Layered Model of Affect" by Patrick Gebhard
FSimplexPADPoint FSimplexPADPoint::Joy = FSimplexPADPoint(0.4f, 0.2f, 0.1f);
FSimplexPADPoint FSimplexPADPoint::Distress = FSimplexPADPoint(-0.4f, -0.2f, -0.5f);
FSimplexPADPoint FSimplexPADPoint::Hope = FSimplexPADPoint(0.2f, 0.2f, -0.1f);
FSimplexPADPoint FSimplexPADPoint::Fear = FSimplexPADPoint(-0.64f, 0.6f, -0.43f);
FSimplexPADPoint FSimplexPADPoint::Love = FSimplexPADPoint(0.3f, 0.1f, 0.2f);
FSimplexPADPoint FSimplexPADPoint::Hate = FSimplexPADPoint(-0.6f, 0.6f, 0.3f);
FSimplexPADPoint FSimplexPADPoint::HappyFor = FSimplexPADPoint(0.4f, 0.2f, 0.2f);
FSimplexPADPoint FSimplexPADPoint::Pitty = FSimplexPADPoint(-0.4f, -0.2f, -0.5f);
FSimplexPADPoint FSimplexPADPoint::Admiration = FSimplexPADPoint(0.5f, 0.3f, -0.2f);
FSimplexPADPoint FSimplexPADPoint::Gloating = FSimplexPADPoint(0.3f, -0.3f, -0.1f);
FSimplexPADPoint FSimplexPADPoint::Pride = FSimplexPADPoint(0.4f, 0.3f, 0.3f);
FSimplexPADPoint FSimplexPADPoint::Shame = FSimplexPADPoint(-0.3f, 0.1f, -0.6f);

float FSimplexPADPoint::Dist(const FSimplexPADPoint& From, const FSimplexPADPoint& To)
{
	return FMath::Sqrt(FMath::Square(From.Pleasure - To.Pleasure) + FMath::Square(From.Arousal - To.Arousal) + FMath::Square(From.Dominance - To.Dominance));
}

FSimplexPADPoint FSimplexPADPoint::InterpTo(const FSimplexPADPoint& Current, const FSimplexPADPoint& Target, float DeltaTime, float InterpSpeed)
{
	if(InterpSpeed <= 0.0f)
	{
		return Target;
	}

	// Difference between colors
	const float Dist = FSimplexPADPoint::Dist(Target, Current);

	// If distance is too small, just set the desired color
	if(Dist < KINDA_SMALL_NUMBER)
	{
		return Target;
	}

	// Delta change, Clamp so we do not over shoot.
	const FSimplexPADPoint DeltaMove = (Target - Current) * FMath::Clamp<float>(DeltaTime * InterpSpeed, 0.0f, 1.0f);

	return Current + DeltaMove;
}

bool FSimplexPADPoint::IsNearlyZero(const FSimplexPADPoint& PADPoint, float Tolerance)
{
	return FMath::Abs(PADPoint.Pleasure) < Tolerance && FMath::Abs(PADPoint.Arousal) < Tolerance && FMath::Abs(PADPoint.Dominance) < Tolerance;
}

TArray<FAIEmotionInformation> FSimplexAppraisalInfo::GetMatchingInformationsFrom(UAIEmotionKnowledge* Source, EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	return Source->Informations.FilterByPredicate(
		[EmotionActionName, SourceActor, TargetActor]
			(const FAIEmotionInformation& information)
			{
				return (information.EmotionActionName == EmotionActionName) && (information.ActionSource.DoesActorMatchTarget(SourceActor)) && (information.ActionTarget.DoesActorMatchTarget(TargetActor));
			}
	);
}

FSimplexAppraisalInfo FSimplexAppraisalInfo::ProcessEmotion(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor, UAIEmotionKnowledge* Knowledge, UAIEmotionKnowledge* Memory)
{
	FSimplexAppraisalInfo Result;

	TArray<FAIEmotionInformation> KnowledgeMatchingInformations = GetMatchingInformationsFrom(Knowledge, EmotionActionName, SourceActor, TargetActor);
	uint32 KnowledgeMatchingInformationNum = KnowledgeMatchingInformations.Num();
	TArray<FAIEmotionInformation> MemoryMatchingInformations = GetMatchingInformationsFrom(Memory, EmotionActionName, SourceActor, TargetActor);
	uint32 MemoryMatchingInformationNum = MemoryMatchingInformations.Num();

	Result.bFromKnowledgeOrMemory = (KnowledgeMatchingInformationNum + MemoryMatchingInformationNum > 0);
	if(!Result.bFromKnowledgeOrMemory)
	{
		return Result;
	}

	float PositiveNegative = 0.0f;
	float KnowledgeMultiplier = 1.0f;
	float WholeAbsoluteValue = 0.0f;
	if(MemoryMatchingInformationNum > 0)
	{
		//Memory is more important than knowledge
		KnowledgeMultiplier = 0.5f;
	}

	for(uint32 i = 0; i < KnowledgeMatchingInformationNum; ++i)
	{
		uint32 EmotionDeltasNum = KnowledgeMatchingInformations[i].EmotionDeltas.Num();
		for(uint32 j = 0; j < EmotionDeltasNum; ++j)
		{
			float Value = KnowledgeMatchingInformations[i].EmotionDeltas[j].EmotionPairDelta;
			PositiveNegative += KnowledgeMultiplier * Value;
			WholeAbsoluteValue += KnowledgeMultiplier * FMath::Abs(Value);
		}
	}
	for(uint32 i = 0; i < MemoryMatchingInformationNum; ++i)
	{
		uint32 EmotionDeltasNum = MemoryMatchingInformations[i].EmotionDeltas.Num();
		for(uint32 j = 0; j < EmotionDeltasNum; ++j)
		{
			float Value = KnowledgeMatchingInformations[i].EmotionDeltas[j].EmotionPairDelta;
			PositiveNegative += KnowledgeMultiplier * Value;
			WholeAbsoluteValue += FMath::Abs(Value);
		}
	}

	Result.Type = PositiveNegative > 0.0f ? ESimplexEmotionType::Positive : (PositiveNegative < 0.0f ? ESimplexEmotionType::Negative : ESimplexEmotionType::Neutral);

	if(!FMath::IsNearlyZero(WholeAbsoluteValue))
	{
		Result.Power = PositiveNegative / WholeAbsoluteValue;
	}

	return Result;
}