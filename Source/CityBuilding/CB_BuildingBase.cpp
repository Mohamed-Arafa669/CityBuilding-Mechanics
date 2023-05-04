// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_BuildingBase.h"
#include "CB_ClickableComponent.h"
#include "CB_PlaceableComponent.h"

// Sets default values
ACB_BuildingBase::ACB_BuildingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	BuildingStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingStaticMesh")); 
	BuildingStaticMesh->SetupAttachment(DefaultRoot);

	ClickableComponent = CreateDefaultSubobject<UCB_ClickableComponent>(TEXT("ClickableComponent"));
	//PlaceableComponent = CreateDefaultSubobject<UCB_PlaceableComponent>(TEXT("PlaceableComponent"));


}

// Called when the game starts or when spawned
void ACB_BuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACB_BuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACB_BuildingBase::AddPlaceableComponent()
{
	if (PlaceableComponentlass)
	{
		PlaceableComponent = NewObject<UCB_PlaceableComponent>(this, PlaceableComponentlass);
		if (PlaceableComponent)
		{
			AddInstanceComponent(PlaceableComponent);
			PlaceableComponent->RegisterComponent();
		}
	}
	
}

