// Fill out your copyright notice in the Description page of Project Settings.

//#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"






ATank* ATankPlayerController::GetControlledTank() const {
	return Cast <ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass <UTankAimingComponent>(); // get the Aim component by find component by class
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent); // call this function in the blueprint, pass the aiming component to blueprint
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("CarterKun : The Aiming Component Can not be found"))
	}
}

//Tick
	//Super
	//AimTowardsCrosshair();

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Ticking!!"));

}



void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(GetControlledTank())) { return;}
	//if it hit the lanscape
	FVector HitLocation;
	if (GetSightRayHitLocation( HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);

	}

	
}

//Get world location if linetrace through crosshair hit lanscape
bool ATankPlayerController::GetSightRayHitLocation(FVector OUT & outHitLocation) const
{
	//Find the crosshair position 
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY); //this is a inside function for getting the screen window size?
	auto ScreenLocation = FVector2D(viewPortSizeX * CrossHairXposition, viewPortSizeY * CrossHairYposition);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

	//"De-project" the screen position of the crosshair to a world direction
	FVector CameraLookDirection;
	if (GetLookDirection(ScreenLocation, CameraLookDirection)) {
		// line-trace along the look direction and see what is hitted 
		//UE_LOG(LogTemp, Warning, TEXT("look direction: %s"), *CameraLookDirection.ToString());
		if (GetLookVecterHitLocation(CameraLookDirection, outHitLocation))
			return true;

	}

	return false;
}

bool ATankPlayerController::GetLookVecterHitLocation(FVector LookDirection, FVector & outHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		outHitLocation =  HitResult.Location;
		return true;
	}
	outHitLocation = FVector(0.);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& CameraLookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, CameraLookDirection);

}