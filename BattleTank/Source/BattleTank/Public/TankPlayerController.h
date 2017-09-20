// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include


class ATank;
class UTankAimingComponent;
/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:


protected:
	// when connected to the blueprint, why we want to put in the protected, because the blueprint is a 
	// subcalss of the C++ code.
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "SetUp")
	void FoundAimingComponent(UTankAimingComponent * AimComRef); // the Aim Com Ref is a type of Tank Aiming Component
	// in the blue print will set the AimComRef to be the TANKAIMINGCOMPONENT menber of the UI widget.

private:

	
	virtual void BeginPlay() override;
	virtual void Tick(float ) override;
	// start the tank moving the barrel  
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector OUT &outHitLocation) const;


	bool GetLookVecterHitLocation(FVector LookDirection, FVector & outHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& CameraLookDirection) const;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXposition = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYposition = 0.333;
	
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 10000000.;


};
