// Fill out your copyright notice in the Description page of Project Settings.

//#include "BattleTank.h"
#include "TankPlayerController.h"




ATank* ATankPlayerController::GetControlledTank() const {
	return Cast <ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto PossesedTank = GetControlledTank();
	if (!PossesedTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s!!"), *PossesedTank->GetName() );
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play!!"));
}
