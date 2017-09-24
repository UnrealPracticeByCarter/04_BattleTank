// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAiController.generated.h"




/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAiController : public AAIController
{
	GENERATED_BODY()
private:

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn * InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossedTankDeath();


protected: //since we want to use them in the child blueprint class
	// how close AI shoudl get close to
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;
	

};
