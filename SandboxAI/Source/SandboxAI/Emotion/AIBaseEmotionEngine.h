// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AIEmotionConstants.h"
#include "AIEmotionKnowledge.h"
#include "AIEmotionState.h"
#include "AIEmotionDecisionInfo.h"
#include "AIBaseEmotionEngine.generated.h"

DECLARE_DELEGATE_OneParam(FPassDecision, const FEmotionDecisionInfo&);

UCLASS(BlueprintType)
class PROJECT_API UAIBaseEmotionEngine : public UObject
{
	GENERATED_BODY()

public:
	FPassDecision OnPassDecision;

protected: //members
	FAIEmotionKnowledge* EmotionKnowledge;

public: //methods
	UAIBaseEmotionEngine();

	/** Used to initialized emotion (knowledge and general) */
	virtual void InitializeEmotionEngine(FAIEmotionKnowledge* emotionKnowledge);	// <<< OVERRIDE <<<
	/** Used to update emotion engine, emotion dynamic and emotion decay go here */
	virtual void TickEmotionEngine(float deltaSeconds);								// <<< OVERRIDE <<<
	/** Used to retrieve emotional state at any time, should be cheap to execute */
	virtual FAIEmotionState GetEmotiomState() const;								// <<< OVERRIDE <<<
	
	FORCEINLINE FAIEmotionKnowledge* GetEmotionKnowledge() const { return EmotionKnowledge; } // <<< USE TO ACCESS KNOWLEDGE <<<

	/**
	 * This is function used to directly influence emotion engine in particular way without interaction with cognition module
	 *@param value - Value of impulse in scale from 0 to 1, will be 
	 */	
	void DirectValencedImpulse(float value, bool bContinuous = false);				// DON't TOuch


protected:
	/** 
	 * Responsible for direct impulse scaling
	 */
	virtual float GetEngineScale() const;											// <<< OVERRIDE <<<

	virtual void DirectValencedImpulseInternal(float value, bool bContinuous);		// <<< OVERRIDE <<<

	/** Use this to pass decisions made by emotion engine */
	void MakeDecision(const FEmotionDecisionInfo& decisionInfo);					// <<< CALL WHEN ENGINE MAKES DECISION <<<
};