// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CB_PlaceableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CITYBUILDING_API UCB_PlaceableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCB_PlaceableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsPlacementValid;
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ValidPlacementMaterial;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* InvalidPlacementMaterial;

	void UpdateState();
	UFUNCTION()
	void OverlapStatusChanged(AActor* OverlappedActor, AActor* OtherActor);

	//UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> OutOverlappingActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ClassFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UActorComponent> ComponentClass;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintPure)
		FORCEINLINE bool GetIsPlacementValid() const { return bIsPlacementValid; }
		
};
