// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiOriginalEngineCore.h"

UAIWasabiOriginalEngineCore::UAIWasabiOriginalEngineCore() :
	Super()
{
	// in default wasabi does calculations in doubles and than clamps then converts them to ints
	ValenceTension = WasabiDefaults::ValenceTension;
	MoodTension = WasabiDefaults::MoodTension;
	Mass = WasabiDefaults::Mass;
	Slope = WasabiDefaults::Slope;
	ValenceBoredomRegion = WasabiDefaults::ValenceBoredomRegion;
	MoodBoredomRegion = WasabiDefaults::MoodBoredomRegion;
	BoredomPerSecond = WasabiDefaults::BoredomPerSecond;
	Prevalence = 0.19f * WasabiDefaults::Prevalence;

	OverrideDominance = 0.0f; // FWasabiConstants::WasabiSpaceRadius;

	bUseTheoryMoodAffecting = false; // whether to use implementation or theory from papers, false is preferable

	ValenceVelocity = 0.0f;
	MoodVelocity = 0.0f;
	WasabiSpacePointVMB = FWasabiSpacePointVMB( 0.0f, Prevalence, 0.0f);
}

void UAIWasabiOriginalEngineCore::Initialize(const FWasabiCharacterTraits& characterTraits)
{
	Super::Initialize(characterTraits);

	WasabiSpacePointVMB = FWasabiSpacePointVMB(0.0f, Prevalence, 0.0f);
	ValenceVelocity = 0.0f;
	MoodVelocity = 0.0f;

	bPendingImpulse = false;
	PendingImpulseValue = 0.0f;

	MapVMBToPAD();

	LastEngineStepState = FWasabiEngineStepState(WasabiSpacePointPAD, WasabiSpacePointVMB, -1, 0.0f);
}
void UAIWasabiOriginalEngineCore::Impulse(float value)
{
	bPendingImpulse = true;
	PendingImpulseValue += value;
}
void UAIWasabiOriginalEngineCore::InternalImpulse(float value)
{
	WasabiSpacePointVMB.SetValence(WasabiSpacePointVMB.GetValence() + value);
	WasabiSpacePointVMB.ClampValenceBySpace();
	ValenceVelocity = 0.0f;
	MoodVelocity = 0.0f;
}

void UAIWasabiOriginalEngineCore::Tick(float DeltaSeconds)
{
	const FWasabiSpacePointVMB lastFrameSpacePointVMB = WasabiSpacePointVMB;

	if (bPendingImpulse) 
	{
		InternalImpulse(PendingImpulseValue);
	}

	// calculate forces
	float valenceForce = -ValenceTension * WasabiSpacePointVMB.GetValence();
	float moodForce = MoodTension * (Prevalence - WasabiSpacePointVMB.GetMood() );

	// Process Valence
	// calculate valence acceleration based on it's position
	float valenceAcceleration = valenceForce / Mass;
	//first calculate delta valence
	float deltaValence = ValenceVelocity * DeltaSeconds + (valenceAcceleration * DeltaSeconds * DeltaSeconds) * 0.5f;
	//then progress velocity in time
	ValenceVelocity += DeltaSeconds * valenceAcceleration;
	
	float valenceSign = FMath::Sign(WasabiSpacePointVMB.GetValence());
	float valenceValue = FMath::Abs(WasabiSpacePointVMB.GetValence());
	
	if (valenceValue > KINDA_SMALL_NUMBER)
	{
		float localDeltaValence = deltaValence / valenceSign;

		if (FMath::Abs(valenceValue) > FMath::Abs(localDeltaValence))
		{
			valenceValue = valenceValue + localDeltaValence;
			WasabiSpacePointVMB.SetValence(valenceValue * valenceSign);
		}
		else 
		{
			localDeltaValence = localDeltaValence + valenceValue;
			valenceValue = 0.0f;
			WasabiSpacePointVMB.SetValence(valenceValue);

			deltaValence = localDeltaValence * valenceSign; // for later use with mood affecting
		}
	}
	else
	{
		WasabiSpacePointVMB.SetValence(0.0f);
		ValenceVelocity = 0.0f;
		deltaValence = 0.0f;
	}
	/* // don't mind me - keep this as explanation for above magic
	value | 50 | 50 | -50 | -50
	delta | 5 | -5 | 5 | -5

	strength | 50 | 50 | 50 | 50
	sign | 1 | 1 | -1 | -1

	velocyty = velocity / sign | 5 = 5 / 1 | -5 = -5 / 1 | -5 = 5 / (-1) | 5 = (-5) / (-1)
	strength = strength + delta | 55 = 50 + 5 | 45 = 50 + (-5) | 45 = 50 + (-5) | 55 = 50 + 5

	value = delta * sign | 55 = 55 * 1 | 45 = 45 * 1 | -45 = 45 * (-1) | -55 = 55 * (-1)
	*/
	
	// Process Mood
	// calculate mood acceleration based on it's position
	float moodAcceleration = moodForce / Mass;
	//first calculate delta valence
	float deltaMood = MoodVelocity * DeltaSeconds + (moodAcceleration * DeltaSeconds * DeltaSeconds) * 0.5f;
	//then progress velocity in time
	MoodVelocity += DeltaSeconds * moodAcceleration;

	float deltaMoodFromValence = 0.0f;
	if (bUseTheoryMoodAffecting)
	{
		deltaMoodFromValence = WasabiSpacePointVMB.GetValence() * deltaValence * Slope; // theory wise
	}
	else
	{
		//deltaMoodFromValence = WasabiSpacePointVMB.GetValence() * (Slope / 100.0f) / Mass; // implementation wise - this was wrong
		deltaMoodFromValence = deltaValence * (Slope / 100.0f) / Mass; // implementation wise
	}
	WasabiSpacePointVMB.SetMood(WasabiSpacePointVMB.GetMood() + deltaMoodFromValence);

	float transformedMood = WasabiSpacePointVMB.GetMood() - Prevalence; // this is done to simplify calculations, operation is reversed after calculations and before clamp
	
	float moodSign = FMath::Sign(transformedMood);
	float moodValue = FMath::Abs(transformedMood);

	if (moodValue > KINDA_SMALL_NUMBER)
	{
		float localDeltaMood = deltaMood / moodSign;

		if (FMath::Abs(moodValue) > FMath::Abs(localDeltaMood))
		{
			moodValue = moodValue + localDeltaMood;
			transformedMood = (moodValue * moodSign);
		}
		else
		{
			localDeltaMood = localDeltaMood + moodValue;
			moodValue = 0.0f;

			deltaValence = localDeltaMood * valenceSign; // for consistency
		}
	}
	else
	{
		transformedMood = 0.0f;
		MoodVelocity = 0.0f;
		deltaMood = 0.0f;
	}

	WasabiSpacePointVMB.SetMood(transformedMood + Prevalence);

	// process Boredom

	bool valenceAllowsForBoredom = FMath::Abs(WasabiSpacePointVMB.GetValence()) < ValenceBoredomRegion;
	bool moodAllowsForBoredom = FMath::Abs(Prevalence - WasabiSpacePointVMB.GetMood()) < MoodBoredomRegion;

	if ( valenceAllowsForBoredom && moodAllowsForBoredom )
	{
		float deltaBoredom = -BoredomPerSecond * DeltaSeconds;
		WasabiSpacePointVMB.SetBoredom(WasabiSpacePointVMB.GetBoredom() + deltaBoredom);
	}
	else
	{
		WasabiSpacePointVMB.SetBoredom(0.0f);
	}

	WasabiSpacePointVMB.ClampValenceBySpace();
	WasabiSpacePointVMB.ClampMoodBySpace();
	WasabiSpacePointVMB.ClampBoredomBySpace();

	MapVMBToPAD();

	LastEngineStepState = FWasabiEngineStepState(WasabiSpacePointPAD, WasabiSpacePointVMB, LastEngineStepState.Index + 1, PendingImpulseValue);
	PendingImpulseValue = 0.0f;
	bPendingImpulse = false;
}

FWasabiEngineStepState UAIWasabiOriginalEngineCore::GetWasabiEngineStepState() const
{
	return LastEngineStepState;
}

void UAIWasabiOriginalEngineCore::MapVMBToPAD()
{
	WasabiSpacePointPAD.SetDominance(OverrideDominance);

	WasabiSpacePointPAD.SetPleasure((WasabiSpacePointVMB.GetValence() + WasabiSpacePointVMB.GetMood()) * 0.5f);
	WasabiSpacePointPAD.SetArousal(FMath::Abs(WasabiSpacePointVMB.GetValence()) + WasabiSpacePointVMB.GetBoredom());
}

void UAIWasabiOriginalEngineCore::MapCharacterTraitsToParams(const FWasabiCharacterTraits& characterTraits)
{
	ValenceTension = WasabiDefaults::ValenceTension * (1.0f + FWasabiCharacterTraits::ConscientiousnessImpactFactor * characterTraits.Conscientiousness);
	MoodTension = WasabiDefaults::MoodTension * (1.0f + FWasabiCharacterTraits::ConscientiousnessImpactFactor * characterTraits.Conscientiousness);
	Slope = WasabiDefaults::Slope * (1.0f + FWasabiCharacterTraits::EmotionalStabilityImpactFactor * characterTraits.EmotionalStability);
	Mass = WasabiDefaults::Mass * (1.0f + FWasabiCharacterTraits::ConscientiousnessImpactFactor * characterTraits.Conscientiousness);
	ValenceBoredomRegion = WasabiDefaults::ValenceBoredomRegion * (1.0f + FWasabiCharacterTraits::SophisticationImpactFactor * characterTraits.Sophistication);
	MoodBoredomRegion = WasabiDefaults::MoodBoredomRegion * (1.0f + FWasabiCharacterTraits::SophisticationImpactFactor * characterTraits.Sophistication);
	BoredomPerSecond = WasabiDefaults::BoredomPerSecond * (1.0f + FWasabiCharacterTraits::SophisticationImpactFactor * characterTraits.Sophistication);
	Prevalence = WasabiDefaults::Prevalence * (0.19f + FWasabiCharacterTraits::ExtraversionImpactFactor * characterTraits.Extraversion);
}