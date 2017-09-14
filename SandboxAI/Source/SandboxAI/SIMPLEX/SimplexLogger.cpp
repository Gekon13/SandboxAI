// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "SimplexLogger.h"
#include "Emotion/AIEmotionComponent.h"
#include "Emotion/Simplex/AISimplexEmotionEngine.h"
#include "FixedPath/EmotionSplineAIController.h"

#include <ctime>

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
		LogText += LoggerInfo[i].SampleName + FString(",");
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
		LogText += FString::Printf(TEXT("\"%.4f\""), LoggerInfo[i].GetLogValue()) + FString(",");
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

	std::time_t timePoint = std::time(NULL);
	std::tm* localTime = std::localtime(&timePoint);

	FString DateString = FString::Printf(TEXT("%d-%d-%d_%d-%d-%d"), localTime->tm_year + 1990, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
	FString FilePath = FString::Printf(TEXT("SIMPLEX_%s.csv"), *DateString);

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

float FSimplexLoggerInfo::GetLogValue() const
{
	if(!SimplexEmotionEngine)
	{
		return 0.0f;
	}

	const FSimplexPADPoint& NeutralPAD = SimplexEmotionEngine->GetNeutralEmotionalState();
	const FSimplexPADPoint& CurrentPAD = SimplexEmotionEngine->GetCurrentEmotionalState();

	return FSimplexPADPoint::Dist(NeutralPAD, CurrentPAD);
}
