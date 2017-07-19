// Fill out your copyright notice in the Description page of Project Settings.
#define _CRT_SECURE_NO_WARNINGS

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

	PrintEvery = 1;
	bCumulateInputValency = true;
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

				//FString someString = FString(TEXT("Hello to the world\r\n"));
				//archive->Serialize((void*)(*someString), someString.Len() * 2); // times two because DWORDS

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
									size_t charSize = sizeof(TCHAR);
									int32 recordNumber = tmpWasabiStatesPtr->Num();
									int32 startLine = 1;
									int32 printCount = recordNumber / PrintEvery;
									float loopLength = 0.0f;

									ASandboxAISplineAIController* splineAIController = Cast<ASandboxAISplineAIController>(tmpAIController);
									if (splineAIController != nullptr)
									{
										loopLength = splineAIController->GetSplineLength();
									}

									FString header = FString::Printf(TEXT("Entity, %s, recordCount, %d, print every, %d, printed, %d, Loop length, %f"), *LogTargets[targetIndex].LogName, recordNumber, PrintEvery, printCount, loopLength);
									header.Append(LINE_TERMINATOR);
									archive->Serialize((void*)(*header), header.Len() * charSize);

									FString columnNames = (*tmpWasabiStatesPtr)[0].ToStringColumnNamesCustom();
									columnNames.Append(LINE_TERMINATOR);
									archive->Serialize((void*)(*columnNames), columnNames.Len() * charSize);

									float valencyAccumulator = 0.0f;
									for (int32 i = startLine; i < recordNumber; ++i)
									{
										valencyAccumulator += (*tmpWasabiStatesPtr)[i].InputValency;
										
										if ((startLine - i) % PrintEvery == 0)
										{
											FString tmpLine = (*tmpWasabiStatesPtr)[i].ToStringLineCustom(valencyAccumulator);
											valencyAccumulator = 0.0f;

											tmpLine.Append(LINE_TERMINATOR);

											archive->Serialize((void*)(*tmpLine), tmpLine.Len() * charSize);
										}
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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Finished printing") );
	}
}

void AWasabiStateLogger::SaveFileHorizontal()
{
	std::time_t timePoint = std::time(NULL);
	std::tm* localTime = std::localtime(&timePoint);

	FString dateTime = FString::Printf(TEXT("%d-%d-%d_%d-%d-%d"), localTime->tm_year + 1990, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

	FString fileName = FString::Printf(TEXT("%s_%s.log"), *LogFilePrefix, *dateTime);

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

			//FString someString = FString(TEXT("Hello to the world\r\n"));
			//archive->Serialize((void*)(*someString), someString.Len() * 2); // times two because DWORDS

			for (int32 targetIndex = 0; targetIndex < LogTargets.Num(); ++targetIndex)
			{
				APawn* pawnToLog = LogTargets[targetIndex].LogTarget;

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
								if (tmpWasabiStatesPtr->Num() > 1)
								{
									int32 startIndex = 1;

									size_t wordSize = sizeof(TCHAR);

									int32 recordNumber = tmpWasabiStatesPtr->Num();
									FString lineEnd = FString(LINE_TERMINATOR);

									FString header = FString::Printf(TEXT("Entity, %s, recordCount, %d"), *LogTargets[targetIndex].LogName, recordNumber);
									header.Append(LINE_TERMINATOR);
									archive->Serialize((void*)(*header), header.Len() * wordSize);

									FString rowName = FString();

									// Index
									rowName = FString(TEXT("Index,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%d,"), (*tmpWasabiStatesPtr)[i].Index);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Pleasure
									rowName = FString(TEXT("Pleasure,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].PAD.GetPleasure());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Arousal
									rowName = FString(TEXT("Arousal,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].PAD.GetArousal());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Dominance
									rowName = FString(TEXT("Dominance,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].PAD.GetDominance());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Valence
									rowName = FString(TEXT("Valence,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].VMB.GetValence());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Mood
									rowName = FString(TEXT("Mood,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].VMB.GetMood());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Boredoom
									rowName = FString(TEXT("Boredoom,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].VMB.GetBoredoom());
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// InputValency
									rowName = FString(TEXT("InputValency,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].InputValency);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Joy
									rowName = FString(TEXT("Joy,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Joy);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Distress
									rowName = FString(TEXT("Distress,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Distress);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// DistanceCovered
									rowName = FString(TEXT("DistanceCovered,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].DistanceCovered);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Speed
									rowName = FString(TEXT("Speed,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Speed);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									// Index
									rowName = FString(TEXT("Index,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%d,"), (*tmpWasabiStatesPtr)[i].Index);
										archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									}
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);
									archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

									//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Saved data to file: %s")));
									
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
			}
			archive->Close();

			UE_LOG(WasabiLog, Warning, TEXT("Saved data to file: %s"), *filePath);
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