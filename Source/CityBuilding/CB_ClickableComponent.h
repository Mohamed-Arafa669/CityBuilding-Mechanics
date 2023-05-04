// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CB_ClickableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CITYBUILDING_API UCB_ClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCB_ClickableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnMouseClicked(AActor* TouchedActor, FKey ButtonPressed);
	UFUNCTION()
		void OnMouseHover(AActor* TouchedActor);
	UFUNCTION()
		void OnMouseHoverEnd(AActor* TouchedActor);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InPlacementMode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TSubclassOf<UActorComponent> ComponentClass;

	UPROPERTY()
	class UStaticMeshComponent* StaticMeshRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Highlighted")
	class UMaterialParameterCollection* HighlightedParam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Highlighted")
	FLinearColor ClickedColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials|Highlighted")
	FLinearColor HoveredColor;


private:

	bool bIsClicked;

		
};
