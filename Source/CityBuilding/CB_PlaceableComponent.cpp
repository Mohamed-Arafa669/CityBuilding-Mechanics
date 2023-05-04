// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_PlaceableComponent.h"

// Sets default values for this component's properties
UCB_PlaceableComponent::UCB_PlaceableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCB_PlaceableComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &ThisClass::OverlapStatusChanged);
	GetOwner()->OnActorEndOverlap.AddDynamic(this, &ThisClass::OverlapStatusChanged);
	UpdateState();

}


void UCB_PlaceableComponent::UpdateState()
{
	GetOwner()->GetOverlappingActors(OutOverlappingActors, ClassFilter);
	bIsPlacementValid = (OutOverlappingActors.Num() == 0);

		TArray<UActorComponent*> OverlappedActorComponents = GetOwner()->GetComponentsByClass(ComponentClass);

		for (UActorComponent* var : OverlappedActorComponents)
		{
		UStaticMeshComponent* SelectedActor = Cast<UStaticMeshComponent>(var);
		if (SelectedActor)
		{
			if (bIsPlacementValid)
			{
			
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Cast Success")));
				SelectedActor->SetMaterial(0, ValidPlacementMaterial);
			}
			else
			{
				SelectedActor->SetMaterial(0, InvalidPlacementMaterial);
			}
		}
	}
}

void UCB_PlaceableComponent::OverlapStatusChanged(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Overlap")));

	UpdateState();
}

// Called every frame
void UCB_PlaceableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

