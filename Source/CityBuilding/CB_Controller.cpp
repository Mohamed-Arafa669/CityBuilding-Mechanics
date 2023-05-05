// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_Controller.h"
#include "CB_ClickableComponent.h"
#include "CB_BuildingBase.h"
#include "CB_PlaceableComponent.h"

void ACB_Controller::BeginPlay()
{
	Super::BeginPlay();
	UpdateBuilding();
}


void ACB_Controller::SetPlacementModeEnabled(bool inIsEnabled)
{
	if (inIsEnabled == bPlacementModeEnabled) return;
	
	else
	{
		bPlacementModeEnabled = inIsEnabled;
		if (bPlacementModeEnabled)
		{
			FVector Location = FVector(0, 0, -1000000.f);
			PlaceableActor = GetWorld()->SpawnActor(PlaceableActorType, &Location);
			if (PlaceableActor)
			{
				UCB_ClickableComponent* HasClickable = Cast<UCB_ClickableComponent>(PlaceableActor->GetComponentByClass(ClickableComponentClass));
				if (HasClickable)
				{
					HasClickable->InPlacementMode();
				}

				if (PlaceableComponentClass)
				{
					ACB_BuildingBase* Building = Cast<ACB_BuildingBase>(PlaceableActor);
					if (Building)
					{
						Building->AddPlaceableComponent();
					}
				}
			}
		}
		else
		{
			if (PlaceableActor)
			{
				PlaceableActor->Destroy();
			}
		}
	}
	

}

void ACB_Controller::UpdatePlacement()
{
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	FHitResult HitResult;
	TraceFunction(HitResult);

	if (HitResult.bBlockingHit)
	{
		if (PlaceableActor)
		{
			PlaceableActor->SetActorLocation(HitResult.Location);
		}
	}
}

void ACB_Controller::UpdateFunction()
{
	if (bPlacementModeEnabled)
	{
		UpdatePlacement();
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::UpdateBuilding, 0.05f, false);
}

void ACB_Controller::UpdateBuilding()
{
	UpdateFunction();
}

void ACB_Controller::SpawnBuilding()
{
	if (PlaceableActor)
	{
		UCB_PlaceableComponent* ValidCheck = Cast<UCB_PlaceableComponent>(PlaceableActor->GetComponentByClass(PlaceableComponentClass));
		if (ValidCheck)
		{
			if (ValidCheck->GetIsPlacementValid())
			{
				FTransform Transform = PlaceableActor->GetActorTransform();
				GetWorld()->SpawnActor(PlaceableActorType, &Transform);
				SetPlacementModeEnabled(false);
				
			}
		}
	}
}

void ACB_Controller::TraceFunction(FHitResult& TraceHitResult)
{
	GetWorld()->LineTraceSingleByChannel(
		TraceHitResult,
		WorldLocation,
		(WorldLocation + WorldDirection * 1000000),
		ECollisionChannel::ECC_GameTraceChannel1
	);
}
