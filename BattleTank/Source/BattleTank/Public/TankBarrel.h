// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downward spped, 1 is max upward speed 
	void Elevate(float RelativeSpeed);

private:

	// all used for the elevation of barrel
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreePerSecond = 10; 

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 40; 

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegrees = 0; 

	
	
};
