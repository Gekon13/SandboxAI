#pragma once

#include "Components/ActorComponent.h"
#include "SandboxAIStructures.h"
#include "SimplexStructures.h"
#include "SimplexEmotionComponent.generated.h"

/**
 * Emotion component based on the SIMPLEX architecture
 * Agent is described by personality (Big Five personality traits a.k.a. Five Factor Model a.k.a. OCEAN)
 * Emotional state is represented by a point in PAD (pleasure, arousal, dominance) space
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOXAI_API USimplexEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Emotions")
		FSimplexPersonality Personality;

	UPROPERTY(EditAnywhere, Category = "Emotions")
		float ReturnToNeutralStateSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		FSimplexPADPoint NeutralEmotionalState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Emotions")
		FSimplexPADPoint CurrentEmotionalState;

public:	
	USimplexEmotionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HandleEmotionStimulusElement(const FEmotionStimulusElement& EmotionStimulusElement);

	FORCEINLINE const FSimplexPADPoint& GetCurrentEmotionalState() const { return CurrentEmotionalState; }
	FORCEINLINE const FSimplexPADPoint& GetNeutralEmotionalState() const { return NeutralEmotionalState; }
};
