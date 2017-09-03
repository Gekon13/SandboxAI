// Fill out your copyright notice in the Description page of Project Settings.
#define _CRT_SECURE_NO_WARNINGS

#include "SandboxAI.h"
#include "WasabiStateLogger.h"
#include "WasabiBaseAIController.h"
#include "Emotion/Wasabi/AIWasabiStructures.h"
#include "Emotion/Wasabi/AIWasabiBaseEngineCore.h"
#include "Emotion/AIEmotionComponent.h"
#include <ctime>
#include <iomanip>

// Sets default values
AWasabiStateLogger::AWasabiStateLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LogFilePrefix = FString( TEXT("WASABI_LOG") );

	PrintEvery = 5;
	bCumulateInputValency = true;

	_cooldownTimer = 0.0f;
	_cooldownLength = 2.5f;
	_bCanLogToFile = true;

	LogColor = FColor::Green;
}

// Called when the game starts or when spawned
void AWasabiStateLogger::BeginPlay()
{
	Super::BeginPlay();
	_cooldownTimer = 0.0f;
	_bCanLogToFile = true;
}

// Called every frame
void AWasabiStateLogger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!_bCanLogToFile)
	{
		_cooldownTimer += DeltaSeconds;
		if (_cooldownTimer > _cooldownLength)
		{
			_bCanLogToFile = true;
		}
	}
}

void AWasabiStateLogger::SaveFile()
{
	const float timeToShow = 10.0f;
	if (_bCanLogToFile)
	{
		_bCanLogToFile = true;
	}
	else
	{
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, timeToShow * 0.5f, LogColor, TEXT("Log to file is on cooldown!"));
		}
		return;
	}

	std::time_t timePoint = std::time(NULL);
	std::tm* localTime = std::localtime(&timePoint);
	
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Start logging to file."));
	}

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

				UAIWasabiEmotionEngine* wasabiEmotionEngine = GetWasabiEmotionEngine(pawnToLog);

				if (wasabiEmotionEngine != nullptr)
				{
					TArray<FWasabiComplexStepState>* tmpWasabiStatesPtr = wasabiEmotionEngine->GetWasabiComplexStateStates();
					if (tmpWasabiStatesPtr != nullptr && tmpWasabiStatesPtr->Num() > 0)
					{
						size_t charSize = sizeof(TCHAR);
						int32 recordNumber = tmpWasabiStatesPtr->Num();
						int32 startLine = 1;
						int32 printCount = recordNumber / PrintEvery;

						FString header = FString::Printf(TEXT("Entity, %s, recordCount, %d, print every, %d, printed, %d"), *LogTargets[targetIndex].LogName, recordNumber, PrintEvery, printCount);
						header.Append(LINE_TERMINATOR);
						archive->Serialize((void*)(*header), header.Len() * charSize);

						FString columnNames = (*tmpWasabiStatesPtr)[0].ToStringColumnNames();
						columnNames.Append(LINE_TERMINATOR);
						archive->Serialize((void*)(*columnNames), columnNames.Len() * charSize);

						float valencyAccumulator = 0.0f;
						for (int32 i = startLine; i < recordNumber; ++i)
						{
							valencyAccumulator += (*tmpWasabiStatesPtr)[i].WasabiEngineStepState.InputValency;

							if ((startLine - i) % PrintEvery == 0)
							{
								FString tmpLine = (*tmpWasabiStatesPtr)[i].ToStringLineOverrideInputValency(valencyAccumulator);
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
						if (GEngine != nullptr)
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Array of states is null or empty."), *fileName));
						}
					}
				}
				archive->Close();

				if (GEngine != nullptr)
				{
					GEngine->AddOnScreenDebugMessage(-1, timeToShow, LogColor, FString::Printf(TEXT("Created log: %s"), *filePath));
				}
			}
			else
			{
				if (GEngine != nullptr)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Failed to open file"), *fileName));
				}
			}
		}
		else
		{
			if (GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("FileManager did not get."), *fileName));
			}
		}
	}
	if (GEngine != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Finished logging."));
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

				UAIWasabiEmotionEngine* wasabiEmotionEngine = GetWasabiEmotionEngine(pawnToLog);
				if (wasabiEmotionEngine != nullptr)
				{
					AController* tmpAIController = pawnToLog->GetController();
					if (tmpAIController != nullptr)
					{
						AWasabiBaseAIController* wasabiBaseAIController = Cast<AWasabiBaseAIController>(tmpAIController);
						if (wasabiBaseAIController != nullptr)
						{
							TArray<FWasabiEngineStepState>* tmpWasabiStatesPtr = wasabiBaseAIController->GetWasabiStepStates();
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

									// Boredom
									rowName = FString(TEXT("Boredom,"));
									archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									for (int32 i = startIndex; i < recordNumber; ++i)
									{
										FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].VMB.GetBoredom());
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

									//// Joy
									//rowName = FString(TEXT("Joy,"));
									//archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									//for (int32 i = startIndex; i < recordNumber; ++i)
									//{
									//	FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Joy);
									//	archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									//}
									//archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);
									//
									//// Distress
									//rowName = FString(TEXT("Distress,"));
									//archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									//for (int32 i = startIndex; i < recordNumber; ++i)
									//{
									//	FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Distress);
									//	archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									//}
									//archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);
									//
									//// DistanceCovered
									//rowName = FString(TEXT("DistanceCovered,"));
									//archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									//for (int32 i = startIndex; i < recordNumber; ++i)
									//{
									//	FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].DistanceCovered);
									//	archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									//}
									//archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);
									//
									//// Speed
									//rowName = FString(TEXT("Speed,"));
									//archive->Serialize((void*)(*rowName), rowName.Len() * wordSize);
									//for (int32 i = startIndex; i < recordNumber; ++i)
									//{
									//	FString tmpString = FString::Printf(TEXT("%f,"), (*tmpWasabiStatesPtr)[i].Speed);
									//	archive->Serialize((void*)(*tmpString), tmpString.Len() * wordSize);
									//}
									//archive->Serialize((void*)(*lineEnd), lineEnd.Len() * wordSize);

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

UAIEmotionComponent* AWasabiStateLogger::GetEmotionComponent(APawn* pawnToInspect)
{
	UAIEmotionComponent* emotionComponentPtr = nullptr;

	if (pawnToInspect != nullptr)
	{
		AController* controller = pawnToInspect->GetController();
		if (controller != nullptr)
		{
			UActorComponent* foundComponent = controller->GetComponentByClass(UAIEmotionComponent::StaticClass());
			if (foundComponent != nullptr)
			{
				emotionComponentPtr = Cast<UAIEmotionComponent>(foundComponent);
			}
		}
	}

	return emotionComponentPtr;
}


UAIWasabiEmotionEngine* AWasabiStateLogger::GetWasabiEmotionEngine(APawn* pawnToInspect)
{
	UAIWasabiEmotionEngine* wasabiEmotionEnginePtr = nullptr;

	if (pawnToInspect != nullptr)
	{
		UAIEmotionComponent* emotionComponent = GetEmotionComponent(pawnToInspect);
		if (emotionComponent != nullptr)
		{
			UAIBaseEmotionEngine* baseEmotionEngine = emotionComponent->GetEmotionEngine();
			if (baseEmotionEngine != nullptr)
			{
				wasabiEmotionEnginePtr = Cast<UAIWasabiEmotionEngine>(baseEmotionEngine);
			}
		}
	}

	return wasabiEmotionEnginePtr;
}