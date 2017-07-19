// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "EmotionSense.h"
#include "EmotionalComponent.h"
#include "ReactsToEmotions.h"
#include "Kismet/GameplayStatics.h"


void UEmotionSense::ReportEmotionEventToAll(UObject* WorldContext, FAppraisal Apprasial, AActor* Instigator) {
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(WorldContext, UReactsToEmotions::StaticClass(), Actors);
	for (auto Actor : Actors) {
		BrodcastApprasial(Apprasial, Actor);
	}
}

void UEmotionSense::ReportEmotionEventToActor(FAppraisal Apprasial, AActor* Actor, AActor* Instigator) {
	if (Actor && !Actor->IsPendingKill() && Actor->GetClass()->ImplementsInterface(UReactsToEmotions::StaticClass())) {
		BrodcastApprasial(Apprasial, Actor);
	}
}

void UEmotionSense::BrodcastApprasial(FAppraisal Apprasial, AActor* Actor) {
	auto EmotionalComponent = Cast<UEmotionalComponent>(Actor->GetComponentByClass(UEmotionalComponent::StaticClass()));
	if (EmotionalComponent) {
		EmotionalComponent->OnSensorUpdated.Broadcast(Apprasial);
	}
}
