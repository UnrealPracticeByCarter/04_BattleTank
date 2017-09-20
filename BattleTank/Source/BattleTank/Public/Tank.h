// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"



class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	
	
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimComponent = nullptr;


private:	
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 7000; 

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternateive : there is a one

	UTankBarrel *Barrel = nullptr; //TODO remove

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTIme = 3.;
	double LastFireTime;
	
	
};
