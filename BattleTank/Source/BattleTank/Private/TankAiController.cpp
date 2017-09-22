// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"







void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

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
		
		//ControlledTank->Fire(); //TODO enable the Fire()
}
