// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexStructures.h"

float FSimplexPADPoint::MaxDistance = 2.0f * FMath::Sqrt(3);
float FSimplexPADPoint::OnePerMaxDistance = 1.0f / MaxDistance;

//PAD values from "ALMA – A Layered Model of Affect" by Patrick Gebhard
FSimplexPADPoint FSimplexPADPoint::Joy = FSimplexPADPoint(0.4f, 0.2f, 0.1f);
FSimplexPADPoint FSimplexPADPoint::Distress = FSimplexPADPoint(-0.4f, -0.2f, -0.5f);
FSimplexPADPoint FSimplexPADPoint::Hope = FSimplexPADPoint(0.2f, 0.2f, -0.1f);
FSimplexPADPoint FSimplexPADPoint::Fear = FSimplexPADPoint(-0.64f, 0.6f, -0.43f);
FSimplexPADPoint FSimplexPADPoint::Love = FSimplexPADPoint(0.3f, 0.1f, 0.2f);
FSimplexPADPoint FSimplexPADPoint::Hate = FSimplexPADPoint(-0.6f, 0.6f, 0.3f);
FSimplexPADPoint FSimplexPADPoint::Happyfor = FSimplexPADPoint(0.4f, 0.2f, 0.2f);
FSimplexPADPoint FSimplexPADPoint::Pitty = FSimplexPADPoint(-0.4f, -0.2f, -0.5f);
FSimplexPADPoint FSimplexPADPoint::Admiration = FSimplexPADPoint(0.5f, 0.3f, -0.2f);
FSimplexPADPoint FSimplexPADPoint::Gloating = FSimplexPADPoint(0.3f, -0.3f, -0.1f);
FSimplexPADPoint FSimplexPADPoint::Pride = FSimplexPADPoint(0.4f, 0.3f, 0.3f);
FSimplexPADPoint FSimplexPADPoint::Shame = FSimplexPADPoint(-0.3f, 0.1f, -0.6f);

FSimplexPADPoint FSimplexPADPoint::GetSafeNormal() const
{
	const float LengthSquared = Pleasure * Pleasure + Arousal * Arousal + Dominance * Dominance;
	if(FMath::IsNearlyZero(LengthSquared) || FMath::IsNearlyEqual(LengthSquared, 1.0f))
	{
		return *this;
	}

	const float Length = FMath::Sqrt(LengthSquared);

	return *this / Length;
}

float FSimplexPADPoint::Dist(const FSimplexPADPoint& From, const FSimplexPADPoint& To)
{
	return FMath::Sqrt(FMath::Square(From.Pleasure - To.Pleasure) + FMath::Square(From.Arousal - To.Arousal) + FMath::Square(From.Dominance - To.Dominance));
}

float FSimplexPADPoint::DistBetween(const FSimplexPADPoint& A, const FSimplexPADPoint& B, const FSimplexPADPoint& Current)
{
	FVector AVec(A.Pleasure, A.Arousal, A.Dominance);
	FVector BVec(B.Pleasure, B.Arousal, B.Dominance);
	FVector CurrentVec(Current.Pleasure, Current.Arousal, Current.Dominance);

	FVector AToB = (BVec - AVec);
	float Dot = FVector::DotProduct(AToB.GetSafeNormal(), CurrentVec - AVec);
	FVector CurrentProjectedToAB = AToB.GetSafeNormal() * Dot / AToB.Size();

	return CurrentProjectedToAB.Size() * OnePerMaxDistance;
}

FSimplexPADPoint FSimplexPADPoint::InterpTo(const FSimplexPADPoint& Current, const FSimplexPADPoint& Target, float DeltaTime, float InterpSpeed)
{
	if(InterpSpeed <= 0.0f)
	{
		return Target;
	}

	// Difference between pad points
	const float Dist = FSimplexPADPoint::Dist(Target, Current);

	// Actual delta change
	const float DeltaChange = DeltaTime * InterpSpeed;

	// If distance is too small or distance is lower than delta change, just set the desired pad point
	if(Dist < KINDA_SMALL_NUMBER || Dist < DeltaChange)
	{
		return Target;
	}

	const FSimplexPADPoint DeltaMove = (Target - Current);

	return Current + DeltaMove.GetSafeNormal() * DeltaChange;
}

bool FSimplexPADPoint::IsNearlyZero(const FSimplexPADPoint& PADPoint, float Tolerance)
{
	return FMath::Abs(PADPoint.Pleasure) < Tolerance && FMath::Abs(PADPoint.Arousal) < Tolerance && FMath::Abs(PADPoint.Dominance) < Tolerance;
}

float FSimplexPADPoint::CalculateEmotionStrength(const FSimplexPADPoint& CurrentState, const FSimplexPADPoint& TargetEmotion)
{
	float Dist = FSimplexPADPoint::Dist(CurrentState, TargetEmotion);

	return 1.0f - Dist * FSimplexPADPoint::OnePerMaxDistance;
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

	Result.bSuccessful = (KnowledgeMatchingInformationNum + MemoryMatchingInformationNum > 0);
	if(!Result.bSuccessful)
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
		Result.Power = FMath::Abs(PositiveNegative) / WholeAbsoluteValue;
	}

	return Result;
}