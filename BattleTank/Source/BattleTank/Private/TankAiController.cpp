// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"







void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAiController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast <ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		//TODO Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPossedTankDeath); // when on death is called we will call the OnPossedTankDeath function 
	}
}

void ATankAiController::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank) || !ensure(AimingComponent)) { return; }

		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		//Fire if ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
}

void ATankAiController::OnPossedTankDeath()
{
	if (!GetPawn()) { return;}
	GetPawn()->DetachFromControllerPendingDestroy();
}
