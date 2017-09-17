// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "engine/World.h"




void UTankTrack::setThrottle(float Throttle) {

	auto Time = GetWorld()->GetTimeSeconds();
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s with throttle %f "), Time, *name, Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}