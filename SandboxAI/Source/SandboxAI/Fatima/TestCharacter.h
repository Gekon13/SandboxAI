// Copyright by Mateusz Polewaczyk

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReactsToEmotions.h"
#include "Perception/AIPerceptionComponent.h"
#include "EmotionalComponent.h"
#include "TestCharacter.generated.h"

UCLASS()
class SANDBOXAI_API ATestCharacter : public ACharacter, public IReactsToEmotions
{
	GENERATED_BODY()

protected:
	ATestCharacter();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void UpdateEmotionVisual_Implementation(FLinearColor Color) override;

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, Category = "AI")
		UAIPerceptionComponent* PerceptionComponent;
	UPROPERTY(EditAnywhere, Category = "AI")
		UEmotionalComponent* EmotionalComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SenseTimeOut;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* EmotionVisualMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName ColorParameterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health;

	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;
	UMaterialInstanceDynamic* EmotionVisualMaterialInstance;

};
