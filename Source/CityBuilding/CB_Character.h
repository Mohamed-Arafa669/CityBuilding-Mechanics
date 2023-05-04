// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CB_Character.generated.h"

UCLASS()
class CITYBUILDING_API ACB_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACB_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForwardBackward(float AxisValue);
	void StrafeRightLeft(float AxisValue);
	void CameraOrbit(float AxisValue);
	void CameraPitch(float AxisValue);
	void ZoomIn();
	void ZoomOut();
	void ZoomCamera(float Value);
	void UpdateMovementSpeed();
	void MouseRightClick();
	void MouseRightRelease();
	void MouseLeftClick();
	void MouseLeftRelease();
	void MouseX(float AxisValue);
	void MouseY(float AxisValue);
	void AddBuilding();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Movement")
		float InitialMovementSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Camera")
		float OrbitSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Camera")
		float CameraMinClamp = 310.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Camera")
		float CameraMaxClamp = 350.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Camera")
		float ZoomSpeed = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Camera Settings|Camera")
		float MinZoom = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings|Camera")
		float MaxZoom = 2000.0f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool bRightButtonPressed;

	class ACB_Controller* PlayerController;

};
