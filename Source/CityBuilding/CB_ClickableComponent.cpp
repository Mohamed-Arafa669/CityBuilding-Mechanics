// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_ClickableComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialParameterCollection.h"
#include <Kismet/KismetMaterialLibrary.h>

// Sets default values for this component's properties
UCB_ClickableComponent::UCB_ClickableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> HighlightedParam_ASSET(TEXT("MaterialParameterCollection'/Game/CityBuilding/PostProcess/BuildingInteractableColor.BuildingInteractableColor'"));

	if (HighlightedParam_ASSET.Succeeded()) HighlightedParam = HighlightedParam_ASSET.Object;
}

// Called every frame
void UCB_ClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCB_ClickableComponent::InPlacementMode()
{
	DestroyComponent();
}

// Called when the game starts
void UCB_ClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnClicked.AddDynamic(this, &ThisClass::OnMouseClicked);
	GetOwner()->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnMouseHover);
	GetOwner()->OnEndCursorOver.AddDynamic(this, &ThisClass::OnMouseHoverEnd);

	if (UActorComponent* OwnerActorComponent = GetOwner()->GetComponentByClass(ComponentClass))
	{
		StaticMeshRef = Cast<UStaticMeshComponent>(OwnerActorComponent);
	}
}


void UCB_ClickableComponent::OnMouseClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	bIsClicked = !bIsClicked;

	if (StaticMeshRef)
	{
		if (bIsClicked)
		{
			if (HighlightedParam)
			{
				UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), HighlightedParam, FName("Color"), ClickedColor);
				StaticMeshRef->SetRenderCustomDepth(true);
			}
		}
		else
		{
			StaticMeshRef->SetRenderCustomDepth(false);
		}
	}

}

void UCB_ClickableComponent::OnMouseHover(AActor* TouchedActor)
{
	if (StaticMeshRef)
	{
		if (HighlightedParam)
		{
			if (bIsClicked) return;

			UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), HighlightedParam, FName("Color"), HoveredColor);
			StaticMeshRef->SetRenderCustomDepth(true);
		}
	}
}

void UCB_ClickableComponent::OnMouseHoverEnd(AActor* TouchedActor)
{
	if (StaticMeshRef)
	{
		if (bIsClicked) return;

		StaticMeshRef->SetRenderCustomDepth(false);
	}
}

