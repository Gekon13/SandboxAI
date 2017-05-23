#include "SandboxAI.h"
#include "SimplexEmotionComponent.h"

USimplexEmotionComponent::USimplexEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	BaseDecayFactor = 0.1f;
	DecayFactor = 1.0f;
	bCanPersonalityInfluenceEmotions = false;
}

void USimplexEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;

	//Calculate DecayFactor as combination of chosen factors in personality
	DecayFactor = Personality.OpennessToExperience - Personality.Conscientiousness + Personality.Neuroticism;
	//Here the DecayFactor values from -3 to 3
	//We need to map decay factor from [-3, 3] to [BaseDecayFactor, 1 + BaseDecayFactor] so it can be easily scaled (if needed) and increased or decreased by some fixed value
	DecayFactor = (DecayFactor + 3.0f) / 6.0f + BaseDecayFactor;
}

void USimplexEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float InterpSpeed = DecayFactor;
	if(!bCanPersonalityInfluenceEmotions)
	{
		InterpSpeed = BaseDecayFactor;
	}

	CurrentEmotionalState = FSimplexPADPoint::InterpTo(CurrentEmotionalState, NeutralEmotionalState, DeltaTime, InterpSpeed);
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Current Emotional State:%s"), *(CurrentEmotionalState.ToString())));
}

void USimplexEmotionComponent::HandleEmotionStimulusElement(const FEmotionStimulusElement& EmotionStimulusElement)
{
	FSimplexPADPoint GeneratedEmotion;
	float EmotionPower = EmotionStimulusElement.Power;

	//High openess increases influence (person that is open to experience is not emotional stable so every emotion has great impact on that person)
	float Influence = Personality.OpennessToExperience;
	//High Conscientiousness decreases influence (Conscientiousness means emotional stability)
	Influence -= Personality.Conscientiousness;

	switch(EmotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		Influence += Personality.Extraversion;
		GeneratedEmotion = FSimplexPADPoint::Joy;
		break;
	case EEmotionStimulusElementType::ENegative:
		Influence += Personality.Neuroticism;
		GeneratedEmotion = FSimplexPADPoint::Distress;
		break;
	default:
		break;
	}

	//Here the influence is in range [-3, 3]
	//We need to map influence to [0, 1] range
	Influence = FMath::Clamp((Influence + 3.0f) / 6.0f, 0.0f, 1.0f);

	if(!bCanPersonalityInfluenceEmotions)
	{
		Influence = 1.0f;
	}
	
	CurrentEmotionalState += GeneratedEmotion * EmotionPower * Influence;
}