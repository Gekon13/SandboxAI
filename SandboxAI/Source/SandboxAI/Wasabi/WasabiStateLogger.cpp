// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiStateLogger.h"
#include <ctime>
#include <iomanip>

// Sets default values
AWasabiStateLogger::AWasabiStateLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LogFilePrefix = FString( TEXT("WASABI_LOG") );

}

// Called when the game starts or when spawned
void AWasabiStateLogger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWasabiStateLogger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWasabiStateLogger::SaveFile()
{
	std::time_t timePoint = std::time(NULL);
	std::tm* localTime = std::localtime(&timePoint);
	
	FString dateTime = FString::Printf(TEXT("%d-%d-%d_%d-%d-%d"), localTime->tm_year + 1990, localTime->tm_mon+1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

	FString fileName = FString::Printf(TEXT("%s_%s.log"),*LogFilePrefix,*dateTime);
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("FileName: %s"),*fileName) );
	}

	IFileManager* fileManager = &IFileManager::Get();
	if (fileManager != nullptr)
	{
		FArchive* archive = fileManager->CreateFileWriter(*fileName);
		if (archive != nullptr)
		{
			FString filePath = fileManager->GetFilenameOnDisk(*fileName);
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("FilePath: %s"), *filePath));
			}

			FString someString = FString(TEXT("Hello to the world"));
			archive->Serialize( (void*)(*someString) , someString.Len() * 2); // times two because DWORDS
			archive->Close();

		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Failed to open file"), *fileName));
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("FileManager did not get."), *fileName));
		}
	}
}