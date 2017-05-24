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