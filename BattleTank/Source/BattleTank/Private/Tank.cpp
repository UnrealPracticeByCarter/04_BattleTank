// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"



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
	Super::BeginPlay(); // Need this so that the Blueprint Beginplay event can actually work

	TankAimComponent = FindComponentByClass<UTankAimingComponent>();
}


void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimComponent)) { return; }
	TankAimComponent->AimAt(HitLocation, LaunchSpeed);

}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReload = (FPlatformTime::Seconds() - LastFireTime)>ReloadTIme;

	if (isReload) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
			Projectile->Launchprojectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
	}
}






