// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void TurretRotate(float RelativeSpeed);

private:
	// all used for the elevation of barrel
	UPROPERTY(EditDefaultsOnly)
	float MaxRotateDegreePerSecond = 25; 


	
	
	
};
