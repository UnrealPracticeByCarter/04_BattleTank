// Fill out your copyright notice in the Description page of Project Settings.

//#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"



void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast <ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		//TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath); // when on death is called we will call the OnPossedTankDeath function 
	}
}


void ATankPlayerController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::BeginPlay()
{

	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass <UTankAimingComponent>(); // get the Aim component by find component by class
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent); // call this function in the blueprint, pass the aiming component to blueprint
	}

}

//Tick
	//Super
	//AimTowardsCrosshair();

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();


}



void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass <UTankAimingComponent>(); // get the Aim component by find component by class
	if (ensure(AimingComponent)) {
		FVector HitLocation;
		bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
		
		if(bGotHitLocation)
			AimingComponent->AimAt(HitLocation);
	}

	
}

//Get world location if linetrace through crosshair hit lanscape
bool ATankPlayerController::GetSightRayHitLocation(FVector OUT & outHitLocation) const
{
	//Find the crosshair position 
	int32 viewPortSizeX, viewPortSizeY;
	GetViewportSize(viewPortSizeX, viewPortSizeY); //this is a inside function for getting the screen window size?
	auto ScreenLocation = FVector2D(viewPortSizeX * CrossHairXposition, viewPortSizeY * CrossHairYposition);


	//"De-project" the screen position of the crosshair to a world direction
	FVector CameraLookDirection;
	if (GetLookDirection(ScreenLocation, CameraLookDirection)) {
		return GetLookVecterHitLocation(CameraLookDirection, outHitLocation);
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


