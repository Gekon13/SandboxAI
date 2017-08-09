// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "PsiAIController.h"

APsiAIController::APsiAIController() : Super()
{
	//Agent drives init
	PsiEmotionsComponent = nullptr;
	Drives.Add(FPsiDrive(0.0f, 0.0f, EPsiDrive::ESafety));
	//Drives.Add(FPsiDrive(0.0f, 0.0f, EPsiDrive::ECuriosity));
//	FActionDelegate first,sec;
//	first.BindUObject(this, &APsiAIController::MoveSlower);
//	sec.BindUObject(this, &APsiAIController::MoveFaster);
//	Knowledge.Add(FKnowledgeStruct(first, EPsiDrive::ESafety));
//	Knowledge.Add(FKnowledgeStruct(sec, EPsiDrive::ESafety));
}

void APsiAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	if (InPawn != nullptr)
	{
		PsiEmotionsComponent = Cast<UPsiEmotions>(InPawn->GetComponentByClass(UPsiEmotions::StaticClass()));
	}
}

void APsiAIController::UnPossess()
{
	Super::UnPossess();
	PsiEmotionsComponent = nullptr;
}

void APsiAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ProcessPsiTheory();
	SetEmotionVisualColor(FMath::Lerp<FLinearColor>(FLinearColor::Green, FLinearColor::Red, (0.5f * (PsiEmotionsComponent->Emotions[0].Value + 1.f))));
}

void APsiAIController::ProcessPsiTheory()
{
	ProcessDrives();
	ProcessMotivations();
	
	GEngine->AddOnScreenDebugMessage(-2, GetWorld()->GetDeltaSeconds(), FColor::Blue, FString::Printf(TEXT("Safety:%.4f"), Drives[0].Value));
	GEngine->AddOnScreenDebugMessage(-3, GetWorld()->GetDeltaSeconds(), FColor::Yellow, FString::Printf(TEXT("SpeedModifier:%.4f"), (0.5f * (PsiEmotionsComponent->Emotions[0].Value + 1.f))));
	//TArray<FKnowledgeStruct> actions;
	//for (int i = 0; i < Knowledge.Num(); ++i)
	//{
	//	if (Knowledge[i].DriveType == Goal.Type)
	//		actions.Add(Knowledge[i]);
	//}

	//if (PsiEmotionsComponent->Emotions[0].Value > 0)
	//{
	//	Knowledge[0].ActionDelegate.Execute(0.5f * (PsiEmotionsComponent->Emotions[0].Value + 1.f));

	//}
	//else if (PsiEmotionsComponent->Emotions[0].Value < 0)
	//{
	//	Knowledge[1].ActionDelegate.Execute(0.5f * (PsiEmotionsComponent->Emotions[0].Value + 1.f));
	//}
}

void APsiAIController::ProcessDrives()
{
	Motivations.Empty();
	for (int i = 0; i < Drives.Num(); ++i)
	{
		if (Drives[i].CheckDriveState())
			Motivations.Add(Drives[i].GenerateMotivation());
	}
}

void APsiAIController::ProcessMotivations()
{
	int index = 0;
	for (int i = 1; i < Motivations.Num(); ++i)
	{
		if (Motivations[i].Value > Motivations[index].Value)
			index = i;
	}
	this->Goal = FPsiGoal(Motivations[index].Value, Motivations[index].Type);
}



void APsiAIController::HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement)
{
	if (PsiEmotionsComponent != nullptr)
	{
		PsiEmotionsComponent->ProcessEmotionStimulusElement(EmotionStimulusElement);
	}

	Drives[0].Value = FMath::Clamp((Drives[0].Value + (EmotionStimulusElement.Power / 100.f) * 0.5f), 0.0f, 1.0f);
	//switch (EmotionStimulusElement.EmotionStimulusElementType)
	//{
	//case EEmotionStimulusElementType::EPositive:
	//	//Drives[1].Value = FMath::Clamp((Drives[1].Value + (EmotionStimulusElement.Power / 100.f) * 0.3f), 0.0f, 1.0f);
	//	break;
	//case EEmotionStimulusElementType::ENegative:
	//	Drives[0].Value = FMath::Clamp((Drives[0].Value + (EmotionStimulusElement.Power / 100.f) * 0.5f), 0.0f, 1.0f);
	//	//Drives[1].Value = FMath::Clamp((Drives[0].Value - (EmotionStimulusElement.Power / 100.f) * 0.3f), 0.0f, 1.0f);
	//	break;
	//}
}

void APsiAIController::MoveSlower(float value)
{
	SetFollowSpeedCoefficient(value);
	Drives[0].Value = FMath::Clamp((Drives[0].Value - 0.005f), 0.0f, 1.0f);
}

void APsiAIController::MoveFaster(float value)
{
	SetFollowSpeedCoefficient(value);
	Drives[0].Value = FMath::Clamp((Drives[0].Value - 0.005f), 0.0f, 1.0f);
}
