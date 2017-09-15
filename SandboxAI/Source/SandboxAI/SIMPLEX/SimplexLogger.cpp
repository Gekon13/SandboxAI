// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexLogger.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "FixedPath/EmotionSplineAIController.h"

// Sets default values
ASimplexLogger::ASimplexLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LogEverySeconds = 0.5f;
}

// Called when the game starts or when spawned
void ASimplexLogger::BeginPlay()
{
	Super::BeginPlay();
	
	LogText = FString("LogI,");
	const uint32 LoggerInfosCount = LoggerInfo.Num();
	for(uint32 i = 0; i < LoggerInfosCount; ++i)
	{
		LoggerInfo[i].Initialize();
		if(bEmotionDeviation || bRun)
		{
			LogText += LoggerInfo[i].SampleName + FString(",");
		}
		else
		{
			LogText += FString::Printf(TEXT("%s, %s, %s,"), *(FString::Printf(TEXT("%s_JD"), *LoggerInfo[i].SampleName)), *(FString::Printf(TEXT("%s_LH"), *LoggerInfo[i].SampleName)), *(FString::Printf(TEXT("%s_HF"), *LoggerInfo[i].SampleName)));
		}
	}
	LogText += FString("\n");

	Timer = 0.0f;
	LogI = 0;
}

void ASimplexLogger::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	SaveToFile();
}

// Called every frame
void ASimplexLogger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	if(Timer < LogEverySeconds)
	{
		return;
	}

	Timer = 0.0f;

	LogText += FString::Printf(TEXT("%i,"), ++LogI);
	const uint32 LoggerInfosCount = LoggerInfo.Num();
	for(uint32 i = 0; i < LoggerInfosCount; ++i)
	{
		if(bRun)
		{
			LogText += FString::Printf(TEXT("\"%.4f\","), LoggerInfo[i].GetRunSpeed());
		}
		else
		{
			if(bEmotionDeviation)
			{
				LogText += FString::Printf(TEXT("\"%.4f\","), LoggerInfo[i].GetEmotionalDeviation());
			}
			else
			{
				LogText += FString::Printf(TEXT("\"%.4f\",\"%.4f\",\"%.4f\","), LoggerInfo[i].GetEmotionPair(EEmotionPairName::Joy_Distress), LoggerInfo[i].GetEmotionPair(EEmotionPairName::Love_Hate), LoggerInfo[i].GetEmotionPair(EEmotionPairName::Hope_Fear));
			}
		}
	}
	LogText += FString("\n");
}

void ASimplexLogger::SaveToFile()
{
	uint32 LogTextLength = LogText.Len();
	for(uint32 i = 0; i < LogTextLength; ++i)
	{
		if(LogText[i] == '.')
		{
			LogText[i] = ',';
		}
	}
	FString FilePath = FString::Printf(TEXT("SIMPLEX_%s.csv"), *LogName);

	IFileManager* FileManager = &IFileManager::Get();
	if(FileManager)
	{
		FArchive* WriteArchive = FileManager->CreateFileWriter(*FilePath);
		if(WriteArchive)
		{
			FString RealFilePath = FileManager->GetFilenameOnDisk(*FilePath);

			UE_LOG(LogTemp, Warning, TEXT("%s saved to %s"), *FilePath, *RealFilePath);

			WriteArchive->Serialize(LogText.GetCharArray().GetData(), LogText.Len() * sizeof(TCHAR));

			WriteArchive->Close();
		}
	}
}

void FSimplexLoggerInfo::Initialize()
{
	if(!PawnToLog)
	{
		return;
	}

	AEmotionSplineAIController* Controller = Cast<AEmotionSplineAIController>(PawnToLog->GetController());
	if(Controller && Controller->EmotionComponent)
	{
		UAIBaseEmotionEngine* Engine = Controller->EmotionComponent->GetEmotionEngine();
		SimplexEmotionEngine = Cast<UAISimplexEmotionEngine>(Engine);
	}
}

float FSimplexLoggerInfo::GetEmotionalDeviation() const
{
	if(!SimplexEmotionEngine)
	{
		return 0.0f;
	}

	const FSimplexPADPoint& NeutralPAD = SimplexEmotionEngine->GetNeutralEmotionalState();
	const FSimplexPADPoint& CurrentPAD = SimplexEmotionEngine->GetCurrentEmotionalState();

	return FSimplexPADPoint::Dist(NeutralPAD, CurrentPAD);
}

float FSimplexLoggerInfo::GetEmotionPair(EEmotionPairName EmotionPair) const
{
	if(!SimplexEmotionEngine)
	{
		return 0.0f;
	}

	float DistFromPositive = 0.0f;
	float DistFromNegative = 0.0f;

	const FSimplexPADPoint& CurrentPAD = SimplexEmotionEngine->GetCurrentEmotionalState();

	switch(EmotionPair)
	{
	case EEmotionPairName::Joy_Distress:
		DistFromPositive = FSimplexPADPoint::Dist(FSimplexPADPoint::Joy, CurrentPAD);
		DistFromNegative = FSimplexPADPoint::Dist(FSimplexPADPoint::Distress, CurrentPAD);
		break;

	case EEmotionPairName::Love_Hate:
		DistFromPositive = FSimplexPADPoint::Dist(FSimplexPADPoint::Love, CurrentPAD);
		DistFromNegative = FSimplexPADPoint::Dist(FSimplexPADPoint::Hate, CurrentPAD);
		break;

	case EEmotionPairName::Hope_Fear:
		DistFromPositive = FSimplexPADPoint::Dist(FSimplexPADPoint::Hope, CurrentPAD);
		DistFromNegative = FSimplexPADPoint::Dist(FSimplexPADPoint::Fear, CurrentPAD);
		break;
	}

	return FMath::Clamp(DistFromPositive - DistFromNegative, 0.0f, 1.0f);
}

float FSimplexLoggerInfo::GetRunSpeed() const
{
	if(!PawnToLog || !PawnToLog->IsA<ACharacter>())
	{
		return 0.0f;
	}

	UCharacterMovementComponent* Movement = ((ACharacter*)PawnToLog)->GetCharacterMovement();
	if(!Movement)
	{
		return 0.0f;
	}

	return Movement->MaxWalkSpeed;
}