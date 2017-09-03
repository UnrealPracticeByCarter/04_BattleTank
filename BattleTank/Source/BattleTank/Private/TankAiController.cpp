// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"





ATank* ATankAiController::GetControlledTank() const {
	return Cast <ATank>(GetPawn());
}

ATank * ATankAiController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
	
	
}

void ATankAiController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController Can not find a player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController find the Player Tnak: %s!!"), *PlayerTank->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play!!"));
}

void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}
