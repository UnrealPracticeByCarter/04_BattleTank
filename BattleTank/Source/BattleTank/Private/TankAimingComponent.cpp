// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "TankBarrel.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}






void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }
	FVector OutlaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	
	
	if (UGameplayStatics::SuggestProjectileVelocity
			(
			this,
			OutlaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace
			)// calculate the OutLaunchVelocity
		)
	{
		auto AimDirection = OutlaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
		MoveTurretTowards(AimDirection);


	}

}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;


	Barrel->Elevate(DeltaRotator.Pitch); 
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(Turret)) { return; }
	auto BarrelRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;


	Turret->TurretRotate(DeltaRotator.Yaw);
}


