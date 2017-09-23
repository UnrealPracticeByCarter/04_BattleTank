// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector WorldSpaceAim);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	EFiringState GetFiringState() const { return FiringState; }
	// Sets default values for this component's properties
	UTankAimingComponent();
protected:


	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving();

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;


	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 7000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternateive : there is a one


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTIme = 3.;

	double LastFireTime;
	FVector AimDirection;
	
	
};
