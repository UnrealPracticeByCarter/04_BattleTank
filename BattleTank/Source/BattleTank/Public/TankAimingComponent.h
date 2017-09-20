// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurret;

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
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	void SetTurrentReference(UTankTurret* TurretToSet);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;


	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	
	
};
