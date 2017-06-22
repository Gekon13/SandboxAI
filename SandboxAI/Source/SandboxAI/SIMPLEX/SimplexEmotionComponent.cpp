#include "SandboxAI.h"
#include "SimplexEmotionComponent.h"

USimplexEmotionComponent::USimplexEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	BaseDecayFactor = 0.1f;
	DecayFactor = 1.0f;
}

void USimplexEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;

	DecayFactor = Personality.GetDecayFactor();
}

void USimplexEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float InterpSpeed = DecayFactor;

	CurrentEmotionalState = FSimplexPADPoint::InterpTo(CurrentEmotionalState, NeutralEmotionalState, DeltaTime, InterpSpeed);
	FString OwnerName = GetOwner()->GetName();
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, OwnerName.Append(FString::Printf(TEXT(", Current Emotional State:%s"), *(CurrentEmotionalState.ToString()))));
}

void USimplexEmotionComponent::HandleEmotionStimulusElement(const FEmotionStimulusElement& EmotionStimulusElement)
{
	FSimplexPADPoint GeneratedEmotion;
	float EmotionPower = EmotionStimulusElement.Power;

	switch(EmotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		GeneratedEmotion = FSimplexPADPoint::Joy;
		break;
	case EEmotionStimulusElementType::ENegative:
		GeneratedEmotion = FSimplexPADPoint::Distress;
		break;
	default:
		break;
	}

	float Influence = Personality.GetInfluenceOnEmotion(EmotionStimulusElement.EmotionStimulusElementType == EEmotionStimulusElementType::EPositive);

	CurrentEmotionalState += GeneratedEmotion * EmotionPower * Influence;
}