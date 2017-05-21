// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SandboxAIBaseCharacter.h"
#include "SandboxAISplineCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOXAI_API ASandboxAISplineCharacter : public ASandboxAIBaseCharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
		TWeakObjectPtr<class ASandboxAISplinePath> SplinePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
		class UStaticMeshComponent* EmotionVisualMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spline")
		FName ColorParameterName;

	UMaterialInstanceDynamic* EmotionVisualMaterialInstance;

public:
	ASandboxAISplineCharacter();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UFUNCTION(BlueprintCallable)
		class USplineComponent* GetSplineComponent() const;

	UFUNCTION(BlueprintCallable)
		void SetEmotionVisualColor(FLinearColor newColor);

};
