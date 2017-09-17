// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:


private:

	ATank* GetControlledTank() const;
	
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