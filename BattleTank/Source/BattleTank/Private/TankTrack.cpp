// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "engine/World.h"




void UTankTrack::setThrottle(float Throttle) {



	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}