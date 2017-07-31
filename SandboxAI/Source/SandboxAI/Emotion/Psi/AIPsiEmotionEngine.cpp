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
}

void UAIPsiEmotionEngine::InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge)
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

}

void UAIPsiEmotionEngine::ProcessPsiTheory()
{
	ProcessDrives();
	ProcessMotivations();

	//GEngine->AddOnScreenDebugMessage(-2, GetWorld()->GetDeltaSeconds(), FColor::Blue, FString::Printf(TEXT("Safety:%.4f"), Drives[0].Value));
	//GEngine->AddOnScreenDebugMessage(-3, GetWorld()->GetDeltaSeconds(), FColor::Yellow, FString::Printf(TEXT("SpeedModifier:%.4f"), (0.5f * (PsiEmotionsComponent->Emotions[0].Value + 1.f))));


}

void UAIPsiEmotionEngine::ProcessDrives()
{
	Motivations.Empty();
	for (int i = 0; i < Drives.Num(); ++i)
	{
		if (Drives[i].CheckDriveState())
			Motivations.Add(Drives[i].GenerateMotivation());
	}
}

void UAIPsiEmotionEngine::ProcessMotivations()
{
	int index = 0;
	for (int i = 1; i < Motivations.Num(); ++i)
	{
		if (Motivations[i].Value > Motivations[index].Value)
			index = i;
	}
	this->Goal = FPsiGoal(Motivations[index].Value, Motivations[index].Type);
}

