// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "CB_Controller.h"

// Sets default values
ACB_Character::ACB_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ACB_Character::BeginPlay()
{
	Super::BeginPlay();
	
	InitialMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
	UpdateMovementSpeed();

}

void ACB_Character::MoveForwardBackward(float AxisValue)
{
	FRotator ControlRotationVector = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(ControlRotationVector),AxisValue);
}

void ACB_Character::StrafeRightLeft(float AxisValue)
{
	FRotator ControlRotationVector = FRotator(0.f, GetControlRotation().Yaw, 0.f);
  	AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRotationVector), AxisValue);	
}

void ACB_Character::CameraOrbit(float AxisValue)
{
	AddControllerYawInput(OrbitSpeed * AxisValue);
}

void ACB_Character::CameraPitch(float AxisValue)
{
	if (SpringArm)
	{
		FRotator CamPitchRotator = FRotator(
			UKismetMathLibrary::ClampAngle(SpringArm->GetComponentRotation().Pitch + OrbitSpeed * AxisValue, CameraMinClamp, CameraMaxClamp),
			SpringArm->GetComponentRotation().Yaw,
			SpringArm->GetComponentRotation().Roll);

		SpringArm->SetWorldRotation(CamPitchRotator);
	}
	
}

void ACB_Character::ZoomIn()
{
	ZoomCamera(-1.f);
}

void ACB_Character::ZoomOut()
{
	ZoomCamera(1.f);
}

void ACB_Character::ZoomCamera(float Value)
{
	if (SpringArm)
	{
		SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength += (ZoomSpeed * Value), MinZoom, MaxZoom);
		UpdateMovementSpeed();
	}
}

void ACB_Character::UpdateMovementSpeed()
{
	if (SpringArm)
	{
		GetCharacterMovement()->MaxWalkSpeed = InitialMovementSpeed * (SpringArm->TargetArmLength / MinZoom);	
	}
}

void ACB_Character::MouseRightClick()
{
	bRightButtonPressed = true;
}

void ACB_Character::MouseRightRelease()
{
	bRightButtonPressed = false;
}

void ACB_Character::MouseLeftClick()
{
	PlayerController = PlayerController == nullptr ? Cast<ACB_Controller>(Controller) : PlayerController;
	if (PlayerController)
	{
		if (PlayerController->GetPlacementModeEnabled())
		{
			PlayerController->SpawnBuilding();
		}
	}
}

void ACB_Character::MouseLeftRelease()
{

}

void ACB_Character::MouseX(float AxisValue)
{
	if (bRightButtonPressed)
	{
		CameraOrbit(AxisValue);
	}
}

void ACB_Character::MouseY(float AxisValue)
{
	if (bRightButtonPressed)
	{
		CameraPitch(AxisValue);
	}
}

void ACB_Character::AddBuilding()
{
	PlayerController = PlayerController == nullptr ? Cast<ACB_Controller>(Controller) : PlayerController;
	if (PlayerController)
	{
		PlayerController->SetPlacementModeEnabled(true);
	}
}

// Called every frame
void ACB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward/Backward", this, &ACB_Character::MoveForwardBackward);
	PlayerInputComponent->BindAxis("StrafeLeft/Right", this, &ACB_Character::StrafeRightLeft);
	PlayerInputComponent->BindAxis("CameraOrbit", this, &ACB_Character::CameraOrbit);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ACB_Character::CameraPitch);
	PlayerInputComponent->BindAxis("MouseX", this, &ACB_Character::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &ACB_Character::MouseY);

	PlayerInputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &ACB_Character::ZoomIn);
	PlayerInputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &ACB_Character::ZoomOut);
	PlayerInputComponent->BindAction("MouseRightClick", IE_Pressed, this, &ACB_Character::MouseRightClick);
	PlayerInputComponent->BindAction("MouseRightClick", IE_Released, this, &ACB_Character::MouseRightRelease);
	PlayerInputComponent->BindAction("MouseLeftClick", IE_Pressed, this, &ACB_Character::MouseLeftClick);
	PlayerInputComponent->BindAction("MouseLeftClick", IE_Released, this, &ACB_Character::MouseLeftRelease);
	PlayerInputComponent->BindAction("Build", IE_Pressed, this, &ACB_Character::AddBuilding);

	
	
}

