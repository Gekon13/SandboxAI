// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAI.h"
#include "WasabiStructures.generated.h"

USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiConstants
{
	GENERATED_BODY()

public:
	static const float WasabiSpaceRadius;

	static const float FWasabiEmotionDefaultInnerRadius;
	static const float FWasabiEmotionDefaultOuterRadius;

	//static const FString ColumnSeparator;
};


USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiSpacePointPAD : public FVector
{
	GENERATED_BODY()

public:
	static const FWasabiSpacePointPAD WasabiSpacePointPADMin;
	static const FWasabiSpacePointPAD WasabiSpacePointPADMax;

	FORCEINLINE FWasabiSpacePointPAD();
	FORCEINLINE FWasabiSpacePointPAD(const FVector& source);
	FORCEINLINE FWasabiSpacePointPAD(const FWasabiSpacePointPAD& source);
	FORCEINLINE FWasabiSpacePointPAD(float Pleasure, float Arousal, float Dominance);

	FORCEINLINE float GetPleasure() { return X; }
	FORCEINLINE const float GetPleasure() const { return X; }
	FORCEINLINE void SetPleasure(const float& Pleasure) { X = Pleasure; }

	FORCEINLINE float GetArousal() { return Y; }
	FORCEINLINE const float GetArousal() const { return Y; }
	FORCEINLINE void SetArousal(const float& Arousal) { Y = Arousal; }

	FORCEINLINE float GetDominance() { return Z; }
	FORCEINLINE const float GetDominance() const { return Z; }
	FORCEINLINE void SetDominance(const float& Dominance) { Z = Dominance; }

	void ClampPleasureBySpace();
	void ClampArousalBySpace();
	void ClampDominanceBySpace();
};

FWasabiSpacePointPAD::FWasabiSpacePointPAD() : Super() { }
FWasabiSpacePointPAD::FWasabiSpacePointPAD(const FVector& source) : Super(source) { }
FWasabiSpacePointPAD::FWasabiSpacePointPAD(const FWasabiSpacePointPAD& source) : Super(source) { }
FWasabiSpacePointPAD::FWasabiSpacePointPAD(float Pleasure, float Arousal, float Dominance) : Super(Pleasure, Arousal, Dominance) { }

USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiSpacePointVMB : public FVector
{
	GENERATED_BODY()

public:
	static const FWasabiSpacePointVMB WasabiSpacePointVMBMin;
	static const FWasabiSpacePointVMB WasabiSpacePointVMBMax;

	FORCEINLINE FWasabiSpacePointVMB();
	FORCEINLINE FWasabiSpacePointVMB(const FVector& source);
	FORCEINLINE FWasabiSpacePointVMB(const FWasabiSpacePointVMB& source);
	FORCEINLINE FWasabiSpacePointVMB(float Pleasure, float Arousal, float Dominance);

	FORCEINLINE float GetValence() { return X; }
	FORCEINLINE const float GetValence() const { return X; }
	FORCEINLINE void SetValence(const float& Valence) { X = Valence; }

	FORCEINLINE float GetMood() { return Y; }
	FORCEINLINE const float GetMood() const { return Y; }
	FORCEINLINE void SetMood(const float& Mood) { Y = Mood; }

	FORCEINLINE float GetBoredoom() { return Z; }
	FORCEINLINE const float GetBoredoom() const { return Z; }
	FORCEINLINE void SetBoredoom(const float& Boredoom) { Z = Boredoom; }

	void ClampValenceBySpace();
	void ClampMoodBySpace();
	void ClampBoredoomBySpace();
};

FWasabiSpacePointVMB::FWasabiSpacePointVMB() : Super() { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(const FVector& source) : Super(source) { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(const FWasabiSpacePointVMB& source) : Super(source) { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(float Valence, float Mood, float BoreDoom) : Super(Valence, Mood, BoreDoom) { }

USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiSpacePointPADEmotion : public FWasabiSpacePointPAD
{
	GENERATED_BODY()
public:
	float InnerRadius;
	float OuterRadius;
	
	FORCEINLINE FWasabiSpacePointPADEmotion();
	FORCEINLINE FWasabiSpacePointPADEmotion(const FVector& source);
	FORCEINLINE FWasabiSpacePointPADEmotion(const FWasabiSpacePointPADEmotion& source);
	FORCEINLINE FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance);
	FORCEINLINE FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance, float InnerRadius, float OuterRadius);

	FORCEINLINE float GetInnerRadius() { return InnerRadius; }
	FORCEINLINE const float GetInnerRadius() const { return InnerRadius; }
	FORCEINLINE void SetInnerRadius(const float& newInnerRadius) { InnerRadius = newInnerRadius; }

	FORCEINLINE float GeOuterRadius() { return OuterRadius; }
	FORCEINLINE const float GetOuterRadius() const { return OuterRadius; }
	FORCEINLINE void SetOuterRadius(const float& newOuterRadius) { OuterRadius = newOuterRadius; }

	static const FWasabiSpacePointPADEmotion Joy;
	static const FWasabiSpacePointPADEmotion Distress;
};

FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion() : Super(), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(const FVector& source) : Super(source), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(const FWasabiSpacePointPADEmotion& source) : Super(source), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance) : Super(Pleasure, Arousal, Dominance), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance, float InnerRadius, float OuterRadius) : Super(Pleasure, Arousal, Dominance), InnerRadius(InnerRadius), OuterRadius(OuterRadius) {}

USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiEngineStepState
{
	GENERATED_BODY()

public:
	FWasabiSpacePointPAD PAD;
	FWasabiSpacePointVMB VMB;
	int32 Index;
	float InputValency;

public:
	FORCEINLINE FWasabiEngineStepState();
	//FORCEINLINE FWasabiEngineStepState(const FWasabiEngineStepState& source);
	FORCEINLINE FWasabiEngineStepState(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 Index, float InputValency);

	virtual FString ToStringColumnNames();
	virtual FString ToStringLine();
};

FWasabiEngineStepState::FWasabiEngineStepState() : PAD(FWasabiSpacePointPAD::ZeroVector), VMB(FWasabiSpacePointVMB::ZeroVector), Index(0), InputValency(0) {}
//FWasabiEngineStepState::FWasabiEngineStepState(const FWasabiEngineStepState& source) : PAD(source.PAD), VMB(source.VMB), StateIndex(source.StateIndex), InputValency(source.InputValency) {}
FWasabiEngineStepState::FWasabiEngineStepState(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 StateIndex, float InputValency) : PAD(PAD), VMB(VMB), Index(Index), InputValency(InputValency) {}

USTRUCT(BlueprintType)
struct SANDBOXAI_API FWasabiEngineStepStateCGI : public FWasabiEngineStepState
{
	GENERATED_BODY()

public:
	float Joy;
	float Distress;
	float DistanceCovered;
	float Speed;

public:
	FORCEINLINE FWasabiEngineStepStateCGI();
	FORCEINLINE FWasabiEngineStepStateCGI(const FWasabiEngineStepState& source);
	FORCEINLINE FWasabiEngineStepStateCGI(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 Index, float InputValency, float Joy = 0.0f, float Distress = 0.0f, float DistanceCovered = 0.0f, float Speed = 0.0f);

	virtual FString ToStringColumnNames() override;
	virtual FString ToStringLine() override;
};

FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI() : FWasabiEngineStepState(), Joy(0.0f), Distress(0.0f), DistanceCovered(0.0f), Speed(0.0f) {}
FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI(const FWasabiEngineStepState& source) : Super(source.PAD, source.VMB, source.Index, source.InputValency), Joy(0.0f), Distress(0.0f), DistanceCovered(0.0f), Speed(0.0f) {}
FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 Index, float InputValency, float Joy, float Distress, float DistanceCovered, float Speed)
	: FWasabiEngineStepState(PAD, VMB, Index, InputValency), Joy(Joy), Distress(Distress), DistanceCovered(DistanceCovered), Speed(Speed) {}

