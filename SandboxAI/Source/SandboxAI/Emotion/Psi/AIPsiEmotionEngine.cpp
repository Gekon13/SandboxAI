// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIPsiEmotionEngine.h"

UAIPsiEmotionEngine::UAIPsiEmotionEngine()
{
	SomeName = TEXT("Psi");
	SomeOtherName = TEXT("Psi");

	Drives.Add(FPsiDrive(0.0f, 0.0f, EPsiDrive::ESafety));

	Emotions.Add(FAISingleEmotionState(EEmotionPrimary::Joy, 0.0f));
	Emotions.Add(FAISingleEmotionState(EEmotionPrimary::Distress, 0.0f));

	knowledge = CreateDefaultSubobject<UAIPsiEmotionKnowledge>(TEXT("PsiKnowledge"));
}

void UAIPsiEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);
}

void UAIPsiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);

	ProcessPsiTheory();
}

FAIEmotionState UAIPsiEmotionEngine::GetEmotiomState() const
{
	return Emotions;
}

float UAIPsiEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAIPsiEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	if (value < 0.0f)
	{
		Emotions[0].Strength -= value;
		Emotions[1].Strength += value;
	}
	else if (value > 0.0f)
	{
		Emotions[0].Strength += value;
		Emotions[1].Strength -= value;
	}
	Drives[0].Value += value;

}

void UAIPsiEmotionEngine::ProcessPsiTheory()
{
	ProcessDrives();
	ProcessMotivations();
	ProcessDrives();

	//Emotions[0].Strength -= 0.001f;
	//Emotions[1].Strength -= 0.001f;
	//Drives[0].Value -= 0.001f;

}

void UAIPsiEmotionEngine::ProcessDrives()
{
	Motivations.Empty();
	for (int i = 0; i < Drives.Num(); ++i)
	{
		if (Drives[i].CheckDriveState())
			Motivations.Add(Drives[i].GenerateMotivation());
	}

	//if motivations.num() / 2.f > drives.num() / 2.f 
	// impact on emotions
}

void UAIPsiEmotionEngine::ProcessMotivations()
{
	int index = 0;
	if (Motivations.Num() > 1)
	{
		for (int i = 1; i < Motivations.Num(); ++i)
		{
			if (Motivations[i].Value > Motivations[index].Value)
				index = i;
		}
	}
	this->Goal = FPsiGoal(Motivations[index].Value, Motivations[index].Type);
}


void UAIPsiEmotionEngine::ProcessGoal()
{
	TArray<FPsiKnowledge> possibleActions;
	UAIPsiEmotionKnowledge* psiK = knowledge;//(UAIPsiEmotionKnowledge*)EmotionKnowledge;
	int size = psiK->Actions.Num();
	for (int i = 0; i < size; ++i)
	{
		if (psiK->Actions[i].Type == Goal.Type)
			possibleActions.Add(psiK->Actions[i]);
	}
	FPsiKnowledge bestAction;
	size = possibleActions.Num();
	for (int i = 0; i < size; ++i)
	{
		bestAction = possibleActions[0];
	}

	MakeDecision(FEmotionDecisionInfo(bestAction.Action, 0.0f));
	size = Drives.Num();
	for (int i = 0; i < size; ++i)
	{
		if (Drives[i].Type == bestAction.Type)
			Drives[i].Value -= 0.01f;
	}
	/*
	TAray<KnowStruct> possibilities;
	foreach(data in knowledge) 
		where data.type == goal.type
		possibilities.Add(data)
	KnowStruct best
	foreach(data in possibilities) 
		where data > best
			data = best
	decision = best
	*/
}

/*
void UAIPsiEmotionEngine::AffectEmotions(knowledge data)
{
	data = personality * data;
	Emotions += data;

}
*/


