// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PsiStructures.h"
#include "SandboxAIStructures.h"
#include "Components/ActorComponent.h"
#include "PsiEmotions.generated.h"

UENUM(BlueprintType)
enum class EPsiEmotion : uint8
{
	EFear = 0 UMETA(DisplayName = "Fear"),
};

USTRUCT(BlueprintType)
struct SANDBOXAI_API FPsiEmotion
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psi")
		EPsiEmotion Type;

public:
	FPsiEmotion() : Value(0), Type(EPsiEmotion::EFear) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOXAI_API UPsiEmotions : public UActorComponent
{
	GENERATED_BODY()

public:	
	TArray<FPsiEmotion> Emotions;
	// Sets default values for this component's properties

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPsiEmotions();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ProcessEmotionStimulusElement(const FEmotionStimulusElement& EmotionStimulusElement);	
};
