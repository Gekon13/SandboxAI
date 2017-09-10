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

	if(!AppraisalInfo.bSuccessful)
	{
		//The consequences of an action are not known... So a little fear comes!
		return FSimplexPADPoint::Fear * 0.1f;
	}

	if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
	{
		//There is no change in emotion state caused by inspected action so there is no generated emotion
		return FSimplexPADPoint();
	}

	float Influence = 1.0f;
	if(Personality)
	{
		Influence = Personality->GetInfluenceOnEmotion(AppraisalInfo.Type == ESimplexEmotionType::Positive);
	}

	if(TargetPawn == Knowledge->ControlledActor)
	{
		//Consequences for self
		return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Joy : FSimplexPADPoint::Distress) * AppraisalInfo.Power * Influence;
	}
	else
	{
		//Consequences for others
		return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Happyfor : FSimplexPADPoint::Pitty)* AppraisalInfo.Power * Influence;
	}
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

	if(!AppraisalInfo.bSuccessful)
	{
		//Oops, the connection of action, source and target is not known... So a little fear comes!
		return FSimplexPADPoint::Fear * 0.1f;
	}

	if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
	{
		//There is no change in emotion state caused by inspected action so there is no generated emotion
		return FSimplexPADPoint();
	}

	float Influence = 1.0f;
	if(Personality)
	{
		Influence = Personality->GetInfluenceOnEmotion(AppraisalInfo.Type == ESimplexEmotionType::Positive);
	}

	if(SourcePawn == Knowledge->ControlledActor)
	{
		//Actions performed by self
		return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Pride : FSimplexPADPoint::Shame) * AppraisalInfo.Power * Influence;
	}
	else
	{
		//Actions performed by others
		return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Admiration : FSimplexPADPoint::Gloating) * AppraisalInfo.Power * Influence;
	}
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

	if(!AppraisalInfo.bSuccessful)
	{
		//Wooo, what an object is that? Or what does it cause?... I feel fear...
		return FSimplexPADPoint::Fear * 0.1f;
	}

	if(AppraisalInfo.Type == ESimplexEmotionType::Neutral)
	{
		//There is no change in emotion state caused by inspected action so there is no generated emotion
		return FSimplexPADPoint();
	}

	float Influence = 1.0f;
	if(Personality)
	{
		Influence = Personality->GetInfluenceOnEmotion(AppraisalInfo.Type == ESimplexEmotionType::Positive);
	}

	return (AppraisalInfo.Type == ESimplexEmotionType::Positive ? FSimplexPADPoint::Love : FSimplexPADPoint::Hate) * AppraisalInfo.Power * Influence;
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
