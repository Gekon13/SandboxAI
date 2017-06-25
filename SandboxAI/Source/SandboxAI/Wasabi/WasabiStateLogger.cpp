// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "WasabiStateLogger.h"
#include "Wasabi/WasabiBaseAIController.h"
#include "Wasabi/WasabiStructures.h"
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

	for (int32 targetIndex = 0; targetIndex < LogTargets.Num(); ++targetIndex)
	{
		APawn* pawnToLog = LogTargets[targetIndex].LogTarget;

		FString fileName = FString::Printf(TEXT("%s_%s_%s.log"), *LogFilePrefix, *dateTime, *LogTargets[targetIndex].LogName);

		UE_LOG(WasabiLog, Log, TEXT("This is my log"));
		UE_LOG(WasabiLog, Warning, TEXT("FileName: %s"), *fileName);

		IFileManager* fileManager = &IFileManager::Get();
		if (fileManager != nullptr)
		{
			FArchive* archive = fileManager->CreateFileWriter(*fileName);
			if (archive != nullptr)
			{
				FString filePath = fileManager->GetFilenameOnDisk(*fileName);

				UE_LOG(WasabiLog, Warning, TEXT("FilePath: %s"), *filePath);

				FString someString = FString(TEXT("Hello to the world\r\n"));
				archive->Serialize((void*)(*someString), someString.Len() * 2); // times two because DWORDS

				if (pawnToLog != nullptr)
				{
					AController* tmpAIController = pawnToLog->GetController();
					if (tmpAIController != nullptr)
					{
						AWasabiBaseAIController* wasabiBaseAIController = Cast<AWasabiBaseAIController>(tmpAIController);
						if (wasabiBaseAIController != nullptr)
						{
							TArray<FWasabiEngineStepStateCGI>* tmpWasabiStatesPtr = wasabiBaseAIController->GetWasabiStepStates();
							if (tmpWasabiStatesPtr != nullptr)
							{
								if (tmpWasabiStatesPtr->Num() > 0)
								{
									FString columnNames = (*tmpWasabiStatesPtr)[0].ToStringColumnNames();
									columnNames.Append(LINE_TERMINATOR);

									archive->Serialize((void*)(*columnNames), columnNames.Len() * 2);

									int32 lineNumber = tmpWasabiStatesPtr->Num();
									for (int32 i = 0; i < lineNumber; ++i)
									{
										FString tmpLine = (*tmpWasabiStatesPtr)[i].ToStringLine();
										tmpLine.Append(LINE_TERMINATOR);

										archive->Serialize((void*)(*tmpLine), tmpLine.Len() * 2);
									}
									//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Saved data to file: %s")));
									UE_LOG(WasabiLog, Warning, TEXT("Saved data to file: %s"), *filePath);
								}
								else
								{
									GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Array is empty")));
								}
							}
							else
							{
								GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Array is null")));
							}
						}
						else
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Failed to cast ai controller to wasabi ai controller")));
						}
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("Pawn returned null ai controller")));
					}
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("pawn is null")));
				}


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
}