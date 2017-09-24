// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAI.h"
#include <initializer_list>
#include "../Containers/AIEmotionConstants.h"
#include "../Containers/AIEmotionState.h"
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

//#define WASABI_EMOTIONS_HAPPY_ANGRY
#define WASABI_EMOTIONS_ALL

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

	static const FWasabiSpacePointVMB ImprovedWasabiSpacePointVMBMin;
	static const FWasabiSpacePointVMB ImprovedWasabiSpacePointVMBMax;

	FORCEINLINE FWasabiSpacePointVMB();
	FORCEINLINE FWasabiSpacePointVMB(const FVector& source);
	FORCEINLINE FWasabiSpacePointVMB(const FWasabiSpacePointVMB& source);
	FORCEINLINE FWasabiSpacePointVMB(float Valence, float Mood, float Boredom);

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

	void ImprovedClampValenceBySpace();
	void ImprovedClampMoodBySpace();
	void ImprovedClampBoredomBySpace();
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InnerRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
	void UpdateEmotionNoDominance(const FWasabiSpacePointPAD& wasabiSpacePointPAD);
	FORCEINLINE FAISingleEmotionState ToSingleEmotionState() const;

protected:
	FORCEINLINE static float DistanceNoDominance(const FWasabiSpacePointPAD& first, const FWasabiSpacePointPAD& second);
};

float FWasabiEmotion::DistanceNoDominance(const FWasabiSpacePointPAD& first, const FWasabiSpacePointPAD& second)
{
	float valence = second.GetPleasure() - first.GetPleasure();
	float mood = second.GetArousal() - first.GetArousal();
	return FMath::Sqrt(valence * valence + mood * mood);
}

namespace WasabiEmotions
{
	const FWasabiEmotion Angry = FWasabiEmotion(EEmotionName::WASABI_Angry, std::initializer_list<FWasabiSpacePointPADEmotion>({ 
		FWasabiSpacePointPADEmotion (80.0f,80.0f,100.0f)
	}) );

	const FWasabiEmotion Annoyed = FWasabiEmotion(EEmotionName::WASABI_Annoyed, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(-50.0f,0.0f,100.0f)
	}));

	const FWasabiEmotion Bored = FWasabiEmotion(EEmotionName::WASABI_Bored, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(0.0f,-80.0f,100.0f)
	}));

	const FWasabiEmotion Concentrated = FWasabiEmotion(EEmotionName::WASABI_Concentrated, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(0.0f,0.0f,100.0f),
		FWasabiSpacePointPADEmotion(0.0f,0.0f,-100.0f)
	}));

	const FWasabiEmotion Depressed = FWasabiEmotion(EEmotionName::WASABI_Depressed, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(0.0f,-80.0f,-100.0f)
	}));

	const FWasabiEmotion Fearful = FWasabiEmotion(EEmotionName::WASABI_Fearful, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(-80.0f,80.0f,100.0f)
	}));

	const FWasabiEmotion Happy = FWasabiEmotion(EEmotionName::WASABI_Happy, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(50.0f,0.0f, 100.0f),
		FWasabiSpacePointPADEmotion(50.0f,0.0f,-100.0f)
	}));

	const FWasabiEmotion Friendly = FWasabiEmotion(EEmotionName::WASABI_Friendly, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(80.0f,80.0f, 100.0f),
		FWasabiSpacePointPADEmotion(80.0f,80.0f,-100.0f)
	}));

	const FWasabiEmotion Sad = FWasabiEmotion(EEmotionName::WASABI_Sad, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(-50.0f,0.0f,-100.0f)
	}));

	const FWasabiEmotion Surprised = FWasabiEmotion(EEmotionName::WASABI_Surprised, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(10.0f,80.0f,100.0f),
		FWasabiSpacePointPADEmotion(10.0f,80.0f,-100.0f)
	}));

	const FWasabiEmotion Anxious = FWasabiEmotion(EEmotionName::WASABI_Extended_Anxious, std::initializer_list<FWasabiSpacePointPADEmotion>({
		FWasabiSpacePointPADEmotion(16.0f,88.0f,-15.0f)
	}));
}

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

USTRUCT(BlueprintType)
struct PROJECT_API FWasabiComplexStepState
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FWasabiEngineStepState WasabiEngineStepState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FAIEmotionState EmotionState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;

	FORCEINLINE FWasabiComplexStepState();
	FORCEINLINE FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState);
	FORCEINLINE FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, const FAIEmotionState& emotionState);
	FORCEINLINE FWasabiComplexStepState(float time);
	FORCEINLINE FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, float time);
	FORCEINLINE FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, const FAIEmotionState& emotionState, float time);

	FString ToStringColumnNames();
	FString ToStringLine();
	FString ToStringLineOverrideInputValency(float inputValency);
};

FWasabiComplexStepState::FWasabiComplexStepState() : WasabiEngineStepState(FWasabiEngineStepState()), EmotionState(FAIEmotionState()), Time(0.0f) {}
FWasabiComplexStepState::FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState) : WasabiEngineStepState(wasabiEngineStepState), EmotionState(FAIEmotionState()), Time(0.0f) {}
FWasabiComplexStepState::FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, const FAIEmotionState& emotionState) : WasabiEngineStepState(wasabiEngineStepState), EmotionState(emotionState), Time(0.0f) {}
FWasabiComplexStepState::FWasabiComplexStepState(float time) : WasabiEngineStepState(FWasabiEngineStepState()), EmotionState(FAIEmotionState()), Time(time) {}
FWasabiComplexStepState::FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, float time) : WasabiEngineStepState(wasabiEngineStepState), EmotionState(FAIEmotionState()), Time(time) {}
FWasabiComplexStepState::FWasabiComplexStepState(const FWasabiEngineStepState& wasabiEngineStepState, const FAIEmotionState& emotionState, float time) : WasabiEngineStepState(wasabiEngineStepState), EmotionState(emotionState), Time(time) {}

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
