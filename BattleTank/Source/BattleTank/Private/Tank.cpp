// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s, CarterKun : Tank c++ construct"), *TankName)
	// No need to protect pointters as added at construction

}


void ATank::BeginPlay() {
	//Super?
	Super::BeginPlay();

}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimComponent) { return; }
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);


}

void ATank::Fire()
{
	bool isReload = (FPlatformTime::Seconds() - LastFireTime)>ReloadTIme;

	if (Barrel && isReload) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
			Projectile->Launchprojectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
	}
}






