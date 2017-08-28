// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AISimplexAppraisalModule.h"

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForConsequences(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* TargetPawn = Cast<APawn>(TargetActor);
	if(!TargetPawn)
	{
		//It's not agent/character so there are no consequences for agents
		return FSimplexPADPoint();
	}

	FSimplexAppraisalInfo AppraisalInfo = FSimplexAppraisalInfo::ProcessEmotion(EmotionActionName, SourceActor, TargetActor, Knowledge, Memory);

	if(TargetPawn == Knowledge->ControlledActor)
	{
		//Consequences for self
		if(AppraisalInfo.bFromKnowledgeOrMemory)
		{
			if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
			{
				return FSimplexPADPoint();
			}

			return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Joy : FSimplexPADPoint::Distress) * AppraisalInfo.Power;
		}
		else
		{
			//No action in knowledge or memory (how should I generate emotions?)
		}
	}
	else
	{
		//Consequences for others
		if(AppraisalInfo.bFromKnowledgeOrMemory)
		{
			if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
			{
				return FSimplexPADPoint();
			}

			return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::HappyFor : FSimplexPADPoint::Pitty)* AppraisalInfo.Power;
		}
		else
		{
			//No action in knowledge or memory (how should I generate emotions?)
		}
	}

	return FSimplexPADPoint();
}

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForActions(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* SourcePawn = Cast<APawn>(SourceActor);
	if(!SourcePawn)
	{
		//It's not agent/character so there are no actions performed by any agent to be considered
		return FSimplexPADPoint();
	}

	FSimplexAppraisalInfo AppraisalInfo = FSimplexAppraisalInfo::ProcessEmotion(EmotionActionName, SourceActor, TargetActor, Knowledge, Memory);

	if(SourcePawn == Knowledge->ControlledActor)
	{
		//Actions performed by self
		if(AppraisalInfo.bFromKnowledgeOrMemory)
		{
			if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
			{
				return FSimplexPADPoint();
			}

			return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Pride : FSimplexPADPoint::Shame) * AppraisalInfo.Power;
		}
		else
		{
			//No action in knowledge or memory (how should I generate emotions?)
		}
	}
	else
	{
		//Actions performed by others
		if(AppraisalInfo.bFromKnowledgeOrMemory)
		{
			if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
			{
				return FSimplexPADPoint();
			}

			return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Admiration : FSimplexPADPoint::Gloating) * AppraisalInfo.Power;
		}
	else
	{
		//No action in knowledge or memory (how should I generate emotions?)
	}
	}

	return FSimplexPADPoint();
}

FSimplexPADPoint UAISimplexAppraisalModule::Internal_DoAppraisalForObjects(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	APawn* SourcePawn = Cast<APawn>(SourceActor);
	APawn* TargetPawn = Cast<APawn>(TargetActor);
	if(SourcePawn && TargetPawn)
	{
		//Both actors are pawn so there was no non-agent object performing action
		return FSimplexPADPoint();
	}

	FSimplexAppraisalInfo AppraisalInfo = FSimplexAppraisalInfo::ProcessEmotion(EmotionActionName, SourceActor, TargetActor, Knowledge, Memory);

	if(AppraisalInfo.bFromKnowledgeOrMemory)
	{
		if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
		{
			return FSimplexPADPoint();
		}

		return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Love : FSimplexPADPoint::Hate) * AppraisalInfo.Power;
	}
	else
	{
		//No action in knowledge or memory (how should I generate emotions?)
	}

	return FSimplexPADPoint();
}

TArray<FSimplexPADPoint> UAISimplexAppraisalModule::DoAppraisal(EEmotionActionName EmotionActionName, AActor* SourceActor, AActor* TargetActor)
{
	TArray<FSimplexPADPoint> GeneratedEmotions;
	FSimplexPADPoint ConsequencesEmotion = Internal_DoAppraisalForConsequences(EmotionActionName, SourceActor, TargetActor);
	FSimplexPADPoint ActionsEmotion = Internal_DoAppraisalForActions(EmotionActionName, SourceActor, TargetActor);
	FSimplexPADPoint ObjectsEmotion = Internal_DoAppraisalForObjects(EmotionActionName, SourceActor, TargetActor);

	if(!FSimplexPADPoint::IsNearlyZero(ConsequencesEmotion))
	{
		GeneratedEmotions.Add(ConsequencesEmotion);
	}

	if(!FSimplexPADPoint::IsNearlyZero(ActionsEmotion))
	{
		GeneratedEmotions.Add(ActionsEmotion);
	}

	if(!FSimplexPADPoint::IsNearlyZero(ObjectsEmotion))
	{
		GeneratedEmotions.Add(ObjectsEmotion);
	}

	return GeneratedEmotions;
}
