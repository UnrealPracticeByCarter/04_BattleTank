// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set the maximum driving force of the tank and try to apply forces on the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = Input)
	void setThrottle(float Throttle);

	//Max force per track in Newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; //assume 40 ton tank and 1g acceleration

private:
	UTankTrack();
	virtual void BeginPlay() override;
	
	void ApplaySidewaysForce();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();
	
	float CurrentThrottle = 0;
};
