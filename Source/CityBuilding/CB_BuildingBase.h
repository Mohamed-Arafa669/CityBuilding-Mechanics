// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityBuilding/CB_ClickableComponent.h"
#include "CB_BuildingBase.generated.h"

UCLASS()
class CITYBUILDING_API ACB_BuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACB_BuildingBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* BuildingStaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCB_ClickableComponent* ClickableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCB_PlaceableComponent* PlaceableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UCB_PlaceableComponent> PlaceableComponentlass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddPlaceableComponent();
};
