#include "SandboxAI.h"
#include "SimplexEmotionComponent.h"

USimplexEmotionComponent::USimplexEmotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ReturnToNeutralStateSpeed = 1.0f;
}

void USimplexEmotionComponent::BeginPlay()
{
	Super::BeginPlay();

	NeutralEmotionalState = Personality.ToPADPoint();
	CurrentEmotionalState = NeutralEmotionalState;
}

void USimplexEmotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentEmotionalState = FSimplexPADPoint::InterpTo(CurrentEmotionalState, NeutralEmotionalState, DeltaTime, ReturnToNeutralStateSpeed);
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Yellow, FString::Printf(TEXT("Current Emotional State:%s"), *(CurrentEmotionalState.ToString())));
}

void USimplexEmotionComponent::HandleEmotionStimulusElement(const FEmotionStimulusElement& EmotionStimulusElement)
{
	switch(EmotionStimulusElement.EmotionStimulusElementType)
	{
	case EEmotionStimulusElementType::EPositive:
		CurrentEmotionalState += FSimplexPADPoint::Joy * EmotionStimulusElement.Power;
		break;
	case EEmotionStimulusElementType::ENegative:
		CurrentEmotionalState += FSimplexPADPoint::Distress * EmotionStimulusElement.Power;
		break;
	default:
		break;
	}
}