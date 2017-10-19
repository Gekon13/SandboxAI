// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIPsiEmotionEngine.h"

UAIPsiEmotionEngine::UAIPsiEmotionEngine()
{
	Drives.Add(FPsiDrive(0.0f, 0.0f, EPsiDrive::ESafety));

	Emotions.Add(FAISingleEmotionState(EEmotionName::Joy, 0.0f));
	Emotions.Add(FAISingleEmotionState(EEmotionName::Distress, 0.0f));

	Personality.Add(FPsiPersonalityTrait("Bravery", 1.0f, EEmotionName::Fear, EPsiDrive::ESafety));
	Personality.Add(FPsiPersonalityTrait("Optimism", 1.0f, EEmotionName::Joy));
	Personality.Add(FPsiPersonalityTrait("Pessimism", 1.0f, EEmotionName::Distress));

	EmotionsToPad.Add(FPsiEmotionToPad(EEmotionName::Joy, FAIEmotionPointPAD(.4f, .2f, .1f), FAIEmotionPointPAD(-.4f, .2f, .5f)));
	EmotionsToPad.Add(FPsiEmotionToPad(EEmotionName::Distress, FAIEmotionPointPAD(-.4f, .2f, .5f), FAIEmotionPointPAD(.4f, .2f, .1f)));
	EmotionsToPad.Add(FPsiEmotionToPad(EEmotionName::Fear, FAIEmotionPointPAD(-.64f, .6f, .43f), FAIEmotionPointPAD(.2f, .2f, -.1f)));

	knowledge = CreateDefaultSubobject<UAIPsiEmotionKnowledge>(TEXT("PsiKnowledge"));
}

void UAIPsiEmotionEngine::InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge)
{
	Super::InitializeEmotionEngine(emotionKnowledge);
}

void UAIPsiEmotionEngine::TickEmotionEngine(float DeltaSeconds)
{
	Super::TickEmotionEngine(DeltaSeconds);

	ProcessPsiTheory(DeltaSeconds);
}

FAIEmotionState UAIPsiEmotionEngine::GetEmotionState() const
{
	return Emotions;
}

FAIEmotionPointPAD UAIPsiEmotionEngine::GetPointPAD()
{
	FAIEmotionPointPAD point = FAIEmotionPointPAD(0.f, 0.f, 0.f);
	int size = Emotions.Num();
	if (!size) return point;
	for (int i = 0; i < size; ++i)
	{
		point += this->GeneratePadEmotion(Emotions[i]);
	}
	return (point / size);
}

float UAIPsiEmotionEngine::GetEngineScale() const
{
	return 1.0f;
}

void UAIPsiEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "psi");
	if (value < 0.0f)
	{
		Emotions[1].Strength += FMath::Abs(value);
	}
	else if (value > 0.0f)
	{
		Emotions[0].Strength += FMath::Abs(value);
	}
	Drives[0].Value = FMath::Clamp(Drives[0].Value + FMath::Abs(value), 0.0f, 1.0f);

}

void UAIPsiEmotionEngine::OnTargetPerceptionUpdated(AActor * Actor, FAIStimulus Stimulus)
{

}

void UAIPsiEmotionEngine::HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor * sourceActor, AActor * targetActor)
{
	for (int i = 0; i < knowledge->Informations.Num(); ++i)
	{
		FAIEmotionInformation info = knowledge->Informations[i];
		if (EmotionActionName == info.EmotionActionName && targetActor->StaticClass() == info.ActionSource.TargetClass)
		{
			for (int j = 0; j < info.EmotionDeltas.Num(); ++j)
			{
				switch (info.EmotionDeltas[j].EmotionPairName)
				{
				case EEmotionPairName::Joy_Distress:
					float value = info.EmotionDeltas[j].EmotionPairDelta;
					if (value > 0)
					{
						Emotions[0].Strength = FMath::Clamp(Emotions[0].Strength + FMath::Abs(value), 0.0f, 1.0f);
					}
					else
					{
						Emotions[1].Strength = FMath::Clamp(Emotions[1].Strength + FMath::Abs(value), 0.0f, 1.0f);
					}
					Drives[0].Value = FMath::Clamp(Drives[0].Value + FMath::Abs(value), 0.0f, 1.0f);
					break;
				}
			}
		}
	}
}

void UAIPsiEmotionEngine::ProcessPsiTheory(float deltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "psi");
	ProcessDrives();
	ProcessMotivations();
	ProcessGoal();

	for (int i = 0; i < Emotions.Num(); ++i)
	{
		Emotions[i].Strength = FMath::Clamp(Emotions[i].Strength - 0.002f * deltaSeconds, 0.0f, 1.0f);
	}
	for (int i = 0; i < Drives.Num(); ++i)
	{
		Drives[i].Value = FMath::Clamp(Drives[i].Value + 0.002f * deltaSeconds, 0.0f, 1.0f);
	}
}

void UAIPsiEmotionEngine::ProcessDrives()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "drive");
	if (Drives.Num() == 0)
	{
		return;
	}

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
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "motve");
	if (Motivations.Num() == 0)
	{
		return;
	}

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
	if(this->Goal.Type == EPsiDrive::ENone)	
	{
		return;
	}
	TArray<FPsiKnowledge> possibleActions;
	FPsiKnowledge bestAction;
	float dominant = 0.0f;

	EmotionKnowledge->Informations.Num();
	int size = knowledge->Actions.Num();
	for (int i = 0; i < size; ++i)
	{
		if (knowledge->Actions[i].Type == Goal.Type)
			possibleActions.Add(knowledge->Actions[i]);
	}

	size = possibleActions.Num();
	for (int i = 0; i < size; ++i)
	{
		bestAction = possibleActions[0];
	}
	dominant = -Emotions[0].Strength;
	if (Emotions[0].Strength < Emotions[1].Strength) dominant = Emotions[1].Strength;
	MakeDecision(FEmotionDecisionInfo(bestAction.Action, 0.5f + (0.5f * dominant)));
}

FAIEmotionPointPAD UAIPsiEmotionEngine::GeneratePadEmotion(FAISingleEmotionState& singleEmotion)
{ 
	FPsiEmotionToPad currentEtP;
	for (int i = 0; i < EmotionsToPad.Num(); ++i)
	{
		if (singleEmotion.Emotion == EmotionsToPad[i].EmotionName)
			currentEtP = EmotionsToPad[i];
	}
	float coefficient = (singleEmotion.Strength + 1.0f) / 2.0f;
	return FMath::Lerp(currentEtP.Positive, currentEtP.Negative, coefficient);
}

/*
void UAIPsiEmotionEngine::AffectEmotions(knowledge data)
{
	data = personality * data;
	Emotions += data;

}
*/


