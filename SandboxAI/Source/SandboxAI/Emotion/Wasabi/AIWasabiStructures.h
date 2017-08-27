// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAI.h"
#include <initializer_list>
#include "../AIEmotionConstants.h"
#include "../AIEmotionState.h"
#include "AIWasabiStructures.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiConstants
{
	GENERATED_BODY()

public:
	static const float WasabiSpaceRadius;

	static const float FWasabiEmotionDefaultInnerRadius;
	static const float FWasabiEmotionDefaultOuterRadius;
};

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiDefaults
{
	GENERATED_BODY()

public:
	static const float ValenceTension;
	static const float MoodTension;
	static const float BoredomTension;
	static const float Slope;
	static const float Mass;
	static const float ValenceBoredomRegion;
	static const float MoodBoredomRegion;
	static const float BoredomPerSecond;
	static const float Prevalence;
	static const float Disequilibrium;
};

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiCustomDefaults
{
	GENERATED_BODY()

public:
	static const float ValenceTension;
	static const float MoodTension;
	static const float BoredomTension;
	static const float Slope;
	static const float Mass;
	static const float ValenceBoredomRegion;
	static const float MoodBoredomRegion;
	static const float BoredomPerSecond;
	static const float Prevalence;
	static const float Disequilibrium;
};

//#define WasabiDefaults FWasabiDefaults
#define WasabiDefaults FWasabiCustomDefaults

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiSpacePointPAD : public FVector
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
struct PROJECT_API FWasabiSpacePointVMB : public FVector
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

	FORCEINLINE float GetBoredom() { return Z; }
	FORCEINLINE const float GetBoredom() const { return Z; }
	FORCEINLINE void SetBoredom(const float& Boredom) { Z = Boredom; }

	void ClampValenceBySpace();
	void ClampMoodBySpace();
	void ClampBoredomBySpace();
};

FWasabiSpacePointVMB::FWasabiSpacePointVMB() : Super() { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(const FVector& source) : Super(source) { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(const FWasabiSpacePointVMB& source) : Super(source) { }
FWasabiSpacePointVMB::FWasabiSpacePointVMB(float Valence, float Mood, float Boredom) : Super(Valence, Mood, Boredom) { }

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiSpacePointPADEmotion : public FWasabiSpacePointPAD
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

	static const FWasabiSpacePointPADEmotion MockJoy;
	static const FWasabiSpacePointPADEmotion MockDistress;
};

FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion() : Super(), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(const FVector& source) : Super(source), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(const FWasabiSpacePointPADEmotion& source) : Super(source), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance) : Super(Pleasure, Arousal, Dominance), InnerRadius(FWasabiConstants::FWasabiEmotionDefaultInnerRadius), OuterRadius(FWasabiConstants::FWasabiEmotionDefaultOuterRadius) {}
FWasabiSpacePointPADEmotion::FWasabiSpacePointPADEmotion(float Pleasure, float Arousal, float Dominance, float InnerRadius, float OuterRadius) : Super(Pleasure, Arousal, Dominance), InnerRadius(InnerRadius), OuterRadius(OuterRadius) {}

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiEmotion
{
	GENERATED_BODY()

public: // members
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEmotionName EmotionName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FWasabiSpacePointPADEmotion> EmotionSpacePoints;

public: // methods
	FORCEINLINE FWasabiEmotion();
	FORCEINLINE FWasabiEmotion(const EEmotionName& emotionName);
	FORCEINLINE FWasabiEmotion(const EEmotionName& emotionName, const FWasabiSpacePointPADEmotion& wasabiSpacePointPADEmotion);
	FORCEINLINE FWasabiEmotion(const EEmotionName& emotionName, const std::initializer_list<FWasabiSpacePointPADEmotion>& wasabiSpacePointPADEmotion);

	void UpdateEmotion(const FWasabiSpacePointPAD& wasabiSpacePointPAD);
	FORCEINLINE FAISingleEmotionState ToSingleEmotionState() const;
};

FWasabiEmotion::FWasabiEmotion() 
	: EmotionName(EEmotionName::None), Strength(0.0f), bActive(false)  {}

FWasabiEmotion::FWasabiEmotion(const EEmotionName& emotionName)
	: EmotionName(emotionName), Strength(0.0f), bActive(false) {}

FWasabiEmotion::FWasabiEmotion(const EEmotionName& emotionName, const FWasabiSpacePointPADEmotion& wasabiSpacePointPADEmotion)
	: EmotionName(emotionName), Strength(0.0f), bActive(false), EmotionSpacePoints(std::initializer_list<FWasabiSpacePointPADEmotion>({ wasabiSpacePointPADEmotion })) {}

FWasabiEmotion::FWasabiEmotion(const EEmotionName& emotionName, const std::initializer_list<FWasabiSpacePointPADEmotion>& wasabiSpacePointPADEmotion)
	: EmotionName(emotionName), Strength(0.0f), bActive(false), EmotionSpacePoints(wasabiSpacePointPADEmotion) {}

FAISingleEmotionState FWasabiEmotion::ToSingleEmotionState() const { return FAISingleEmotionState(EmotionName, Strength, bActive); }

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiEngineStepState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWasabiSpacePointPAD PAD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWasabiSpacePointVMB VMB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InputValency;

public:
	FORCEINLINE FWasabiEngineStepState();
	//FORCEINLINE FWasabiEngineStepState(const FWasabiEngineStepState& source);
	FORCEINLINE FWasabiEngineStepState(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 Index, float InputValency);

	virtual FString ToStringColumnNames();
	virtual FString ToStringLine();
	virtual FString ToStringLineOverrideInputValency(float inputValency);
};

FWasabiEngineStepState::FWasabiEngineStepState() : PAD(FWasabiSpacePointPAD::ZeroVector), VMB(FWasabiSpacePointVMB::ZeroVector), Index(0), InputValency(0) {}
//FWasabiEngineStepState::FWasabiEngineStepState(const FWasabiEngineStepState& source) : PAD(source.PAD), VMB(source.VMB), StateIndex(source.StateIndex), InputValency(source.InputValency) {}
FWasabiEngineStepState::FWasabiEngineStepState(const FWasabiSpacePointPAD& iPAD, const FWasabiSpacePointVMB& iVMB, int32 iIndex, float iInputValency) : PAD(iPAD), VMB(iVMB), Index(iIndex), InputValency(iInputValency) {}

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiEngineStepStateCGI : public FWasabiEngineStepState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Joy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Distress;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceCovered;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

public:
	FORCEINLINE FWasabiEngineStepStateCGI();
	FORCEINLINE FWasabiEngineStepStateCGI(const FWasabiEngineStepState& source);
	FORCEINLINE FWasabiEngineStepStateCGI(const FWasabiSpacePointPAD& PAD, const FWasabiSpacePointVMB& VMB, int32 Index, float InputValency, float Joy = 0.0f, float Distress = 0.0f, float DistanceCovered = 0.0f, float Speed = 0.0f);

	virtual FString ToStringColumnNames() override;
	virtual FString ToStringLine() override;
	virtual FString ToStringLineOverrideInputValency(float inputValency) override;

	FString ToStringColumnNamesCustom();
	FString ToStringLineCustom(float inputValency);
};

FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI() : FWasabiEngineStepState(), Joy(0.0f), Distress(0.0f), DistanceCovered(0.0f), Speed(0.0f) {}
FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI(const FWasabiEngineStepState& source) : Super(source.PAD, source.VMB, source.Index, source.InputValency), Joy(0.0f), Distress(0.0f), DistanceCovered(0.0f), Speed(0.0f) {}
FWasabiEngineStepStateCGI::FWasabiEngineStepStateCGI(const FWasabiSpacePointPAD& iPAD, const FWasabiSpacePointVMB& iVMB, int32 iIndex, float iInputValency, float iJoy, float iDistress, float iDistanceCovered, float iSpeed)
	: FWasabiEngineStepState(iPAD, iVMB, iIndex, iInputValency), Joy(iJoy), Distress(iDistress), DistanceCovered(iDistanceCovered), Speed(iSpeed) {}


UENUM(BlueprintType)
enum class EWasabiCoreType : uint8
{
	Original = 0,
	Improved = 1,
};

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiCharacterTraits
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Extraversion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Agreeableness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Conscientiousness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EmotionalStability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Sophistication;

	static const float ExtraversionImpactFactor;
	static const float AgreeablenessImpactFactor;
	static const float ConscientiousnessImpactFactor;
	static const float EmotionalStabilityImpactFactor;
	static const float SophisticationImpactFactor;

public:
	FORCEINLINE FWasabiCharacterTraits();
	FORCEINLINE FWasabiCharacterTraits(float extraversion, float agreeableness, float conscientiousness, float emotionalStability, float sophistication);

	void Validate();
};

FWasabiCharacterTraits::FWasabiCharacterTraits() :
	Extraversion(0.0f), Agreeableness(0.0f), Conscientiousness(0.0f), EmotionalStability(0.0f), Sophistication(0.0f)
{
}

FWasabiCharacterTraits::FWasabiCharacterTraits(float extraversion, float agreeableness, float conscientiousness, float emotionalStability, float sophistication) :
	Extraversion(extraversion), Agreeableness(agreeableness), Conscientiousness(conscientiousness), EmotionalStability(emotionalStability), Sophistication(sophistication)
{
	Validate();
}
