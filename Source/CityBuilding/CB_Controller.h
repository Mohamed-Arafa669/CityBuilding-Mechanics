// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CB_Controller.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API ACB_Controller : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
	void UpdatePlacement();

	
	UFUNCTION()
		void TraceFunction(FHitResult& TraceHitResult);

	FVector WorldLocation;
	FVector WorldDirection;

	UPROPERTY()
	bool bPlacementModeEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlaceableActorType ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* PlaceableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UActorComponent> ClickableComponentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UActorComponent> PlaceableComponentClass;

private:

	UFUNCTION()
		void UpdateFunction();
	UFUNCTION()
		void UpdateBuilding();

public:

	void SpawnBuilding();
	void SetPlacementModeEnabled(bool inIsEnabled);

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetPlacementModeEnabled() const { return bPlacementModeEnabled; }

};
