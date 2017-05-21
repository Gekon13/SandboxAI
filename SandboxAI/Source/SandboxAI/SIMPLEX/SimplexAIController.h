#pragma once

#include "FixedPath/SandboxAISplineAIController.h"
#include "SimplexAIController.generated.h"

/**
 * AI Controller for Simplex based agent with EBDI decision making system
 */
UCLASS()
class SANDBOXAI_API ASimplexAIController : public ASandboxAISplineAIController
{
	GENERATED_BODY()
	
protected:
	class USimplexEmotionComponent* SimplexEmotionComponent;

public:
	ASimplexAIController();

	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	void UpdateEmotionalStateConsequences();

	virtual void HandleEmotionStimulusElement_Implementation(FEmotionStimulusElement EmotionStimulusElement) override;
	
};
