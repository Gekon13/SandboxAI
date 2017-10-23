// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Common/AIEmotionConstants.h"
#include "Common/AIEmotionKnowledge.h"
#include "Common/AIEmotionState.h"
#include "Common/AIEmotionDecisionInfo.h"
#include "Common/AIEmotionPointPAD.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AIPerceptionSystem.h"
#include "AIBaseEmotionEngine.generated.h"

DECLARE_DELEGATE_OneParam(FPassDecision, const FEmotionDecisionInfo&);

/*

legacy interface
ASandboxAIBaseAIController::HandleEmotionStimulusElement -> UAIBaseEmotionEngine::DirectValencedImpulseInternal(float value, bool bContinuous)
!this is for this sprint only!

This one is used to register and unregister to and from delagates, engine can implement custom cognition
UAIBaseEmotionEngine::OnTargetPerceptionUpdated
!this is for later!


for speed we use
ASandboxAISplineAIController::SetFollowSpeedCoefficient(0.5f) -> MakeDecision(FEmotionDecisionInfo(EmotionKnowledge->AvailableActionNames[0], 0.5f));

*/


UCLASS(BlueprintType)
class PROJECT_API UAIBaseEmotionEngine : public UObject
{
	GENERATED_BODY()

public:
	FPassDecision OnPassDecision;

protected: //members
	UAIEmotionKnowledge* EmotionKnowledge;

	/** Whether OnTargetPerceptionUpdated should be called on particular engine */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDoesImplementCustomCongition;

public: //methods
	UAIBaseEmotionEngine();

	/** Used to initialized emotion (knowledge and general) */
	virtual void InitializeEmotionEngine(UAIEmotionKnowledge* emotionKnowledge);	// <<< OVERRIDE <<<
	/** Used to update emotion engine, emotion dynamic and emotion decay go here */
	virtual void TickEmotionEngine(float deltaSeconds);								// <<< OVERRIDE <<<
	/** Used to retrieve emotional state at any time, should be cheap to execute */
	UFUNCTION(BlueprintCallable)
	virtual FAIEmotionState GetEmotionState() const;								// <<< OVERRIDE <<<
	
	FORCEINLINE UAIEmotionKnowledge* GetEmotionKnowledge() const { return EmotionKnowledge; } // <<< USE TO ACCESS KNOWLEDGE <<<

	/**
	 * This is function used to directly influence emotion engine in particular way without interaction with cognition module
	 *@param value - Value of impulse in scale from 0 to 1, will be 
	 */	
	void DirectValencedImpulse(float value, bool bContinuous = false);				// Deprecated, but could be used to debuggin in some cases

	// from AIPerceptionComponent.h
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorPerceptionUpdatedDelegate, AActor*, Actor, FAIStimulus, Stimulus);

	//callback used by Teyon from AIPerceptionComponent, there will be call in here some day, so think about implementation
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);	// <<< CAN OVERRIDE <<< only if custom cognition in implemented and set

	FORCEINLINE bool DoesImplementCustomCognition() const { return bDoesImplementCustomCongition; }

	// from AIEmotionConstants.h
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEmotionActionPerformed, EEmotionActionName, EmotionActionName, AActor*, sourceActor, AActor*, targetActor);

	UFUNCTION()
	virtual void HandleEmotionActionPerformed(EEmotionActionName EmotionActionName, AActor* sourceActor, AActor* targetActor);  // <<<  OVERRIDE  <<<

	UFUNCTION(BlueprintCallable)
	virtual FAIEmotionPointPAD GetPointPAD();                                       // new function used to get unified emotional state

protected:
	/** 
	 * Responsible for direct impulse scaling
	 */
	virtual float GetEngineScale() const;											// <<< OVERRIDE <<<

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);		// <<< OVERRIDE <<< fake input

	/** Method used by derrived engines to pass decisions outside */
	void MakeDecision(const FEmotionDecisionInfo& decisionInfo);					// <<< CALL WHEN ENGINE MAKES DECISION (during tick) <<<
};