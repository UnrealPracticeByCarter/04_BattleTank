// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tank.h"








void ATankAiController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAiController::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast <ATank>(GetPawn());
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ControlledTank) { return ; }

	if (PlayerTank) {

		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if ready
		
		ControlledTank->Fire();
	}

}
