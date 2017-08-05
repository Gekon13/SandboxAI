// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxAI.h"
#include "AIWasabiOriginalEngineCore.h"

UAIWasabiOriginalEngineCore::UAIWasabiOriginalEngineCore() :
	Super()
{
	// in default wasabi does calculations in doubles and than clamps then converts them to ints
	ValenceTension = 140.0f; // default from wasabi is 69 // my later default was 70
	MoodTension = 20.0f; // default from wasabi is 10
	Mass = 5000.0f; // default from wasabi is 5000
	Temperament = 500.0f; // default from wasabi is 500 // in wasabi engine it's called Slope
	ValenceBoredoomRegion = 5.0f; // default from wasabi is 5
	MoodBoredoomRegion = 5.0f; // default from wasabi is 5
	BoredoomPerSecond = 10.0f; // default from wasabi is 50
	Prevalence = 30.0f; // default from wasabi is 30

	OverrideDominance = -FWasabiConstants::WasabiSpaceRadius;

	bUseTheoryMoodAffecting = false; // whether to use implementation or theory from papers
	bValenceAffectMood = true;

	ValenceVelocity = 0.0f;
	MoodVelocity = 0.0f;
	WasabiSpacePointVMB = FWasabiSpacePointVMB( 0.0f, Prevalence, 0.0f);
}

void UAIWasabiOriginalEngineCore::Initialize()
{
	Super::Initialize();

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

	if (bUseTheoryMoodAffecting)
	{
		float deltaMoodFromValence = WasabiSpacePointVMB.GetValence() * deltaValence * Temperament; // theory wise
		if (bValenceAffectMood)
		{
			//deltaMood += deltaMoodFromValence;
			WasabiSpacePointVMB.SetMood(WasabiSpacePointVMB.GetMood() + deltaMoodFromValence);
		}
	}
	else
	{
		float deltaMoodFromValence = WasabiSpacePointVMB.GetValence() * (Temperament / 100.0f) / Mass; // implementation wise
		if (bValenceAffectMood)
		{
			WasabiSpacePointVMB.SetMood(WasabiSpacePointVMB.GetMood() + deltaMoodFromValence);
		}
	}

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

	// process Boredoom

	bool valenceAllowsForBoredoom = FMath::Abs(WasabiSpacePointVMB.GetValence()) < ValenceBoredoomRegion;
	bool moodAllowsForBoredoom = FMath::Abs(Prevalence - WasabiSpacePointVMB.GetMood()) < MoodBoredoomRegion;

	if ( valenceAllowsForBoredoom && moodAllowsForBoredoom )
	{
		float deltaBoredoom = -BoredoomPerSecond * DeltaSeconds;
		WasabiSpacePointVMB.SetBoredoom(WasabiSpacePointVMB.GetBoredoom() + deltaBoredoom);
	}
	else
	{
		WasabiSpacePointVMB.SetBoredoom(0.0f);
	}

	WasabiSpacePointVMB.ClampValenceBySpace();
	WasabiSpacePointVMB.ClampMoodBySpace();
	WasabiSpacePointVMB.ClampBoredoomBySpace();

	MapVMBToPAD();

	LastEngineStepState = FWasabiEngineStepState(WasabiSpacePointPAD, WasabiSpacePointVMB, LastEngineStepState.Index + 1, PendingImpulseValue);
	PendingImpulseValue = 0.0f;
	bPendingImpulse = false;
}

FWasabiEngineStepState UAIWasabiOriginalEngineCore::GetEngineStateState()
{
	return LastEngineStepState;
}

void UAIWasabiOriginalEngineCore::MapVMBToPAD()
{
	WasabiSpacePointPAD.SetDominance(OverrideDominance);

	WasabiSpacePointPAD.SetPleasure((WasabiSpacePointVMB.GetValence() + WasabiSpacePointVMB.GetMood()) * 0.5f);
	WasabiSpacePointPAD.SetArousal(FMath::Abs(WasabiSpacePointVMB.GetValence()) + WasabiSpacePointVMB.GetBoredoom());
}