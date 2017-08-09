// Copyright by Mateusz Polewaczyk

#include "SandboxAI.h"
#include "TestCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "EmotionStimulusFatima.h"
#include "EmotionSourceComponent.h"


ATestCharacter::ATestCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -97));
	GetMesh()->RelativeRotation.Yaw = -90.f;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	EmotionVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Emotion Visual"));
	EmotionVisualMesh->SetupAttachment(RootComponent);
	EmotionVisualMesh->SetRelativeLocation(FVector::UpVector * 200.0f);

	ColorParameterName = FName(TEXT("EmotionColor"));

	EmotionVisualMaterialInstance = nullptr;
	SenseTimeOut = 60.f;

	Health = 30.f;

	FAISenseAffiliationFilter SenseAffiliationFilter;
	SenseAffiliationFilter.bDetectEnemies = true;
	SenseAffiliationFilter.bDetectFriendlies = true;
	SenseAffiliationFilter.bDetectNeutrals = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2500.f;
	SightConfig->LoseSightRadius = 2600.f;
	SightConfig->PeripheralVisionAngleDegrees = 65.f;
	SightConfig->SetMaxAge(SenseTimeOut);
	SightConfig->DetectionByAffiliation = SenseAffiliationFilter;
	PerceptionComponent->ConfigureSense(*SightConfig);

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 3000;
	HearingConfig->LoSHearingRange = 3500;
	HearingConfig->DetectionByAffiliation = SenseAffiliationFilter;
	HearingConfig->SetMaxAge(SenseTimeOut);
	PerceptionComponent->ConfigureSense(*HearingConfig);

	EmotionalComponent = CreateDefaultSubobject<UEmotionalComponent>(TEXT("EmotionalComponent"));
}

void ATestCharacter::BeginPlay() {
	Super::BeginPlay();

	if (PerceptionComponent) {
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATestCharacter::OnTargetPerceptionUpdated);
	}
	EmotionalComponent->AddGoal(FGoal(&Health, 75.f, "Lots of HP"));
}

void ATestCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	Health += DeltaSeconds;
}

void ATestCharacter::UpdateEmotionVisual_Implementation(FLinearColor Color) {
	if (!EmotionVisualMaterialInstance) {
		auto Material = EmotionVisualMesh->GetMaterial(0);
		EmotionVisualMaterialInstance = EmotionVisualMesh->CreateDynamicMaterialInstance(0, Material);
	}
	if (EmotionVisualMaterialInstance) {
		EmotionVisualMaterialInstance->SetVectorParameterValue(ColorParameterName, Color);
	}

}

void ATestCharacter::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {
	auto EmotionSourceComponent = Cast<UEmotionSourceComponent>(Actor->GetComponentByClass(UEmotionSourceComponent::StaticClass()));
	if (EmotionSourceComponent) {
		auto EmotionalComponent = Cast<UEmotionalComponent>(GetComponentByClass(UEmotionalComponent::StaticClass()));
		if (EmotionalComponent) {
			if (EmotionSourceComponent->bContinuous) {
				if (Stimulus.WasSuccessfullySensed()) {
					EmotionalComponent->AddContinuousStimulus(FEmotionStimulusFatima(&EmotionSourceComponent->Appraisal, Actor, &Stimulus));
				} else {
					EmotionalComponent->RemoveContinuousStimulus(Actor);
				}
			} else if (Stimulus.WasSuccessfullySensed()) {
				EmotionalComponent->OnSensorUpdated.Broadcast(EmotionSourceComponent->Appraisal);
			}
		}
	}
}
