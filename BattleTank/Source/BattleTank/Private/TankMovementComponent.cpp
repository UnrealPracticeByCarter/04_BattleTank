// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"




void UTankMovementComponent::IntendMoveForward(float Throw) {

	UE_LOG(LogTemp, Warning, TEXT(" Intend to move forward with Throw: %f "),  Throw);
	LeftTrack->setThrottle(Throw);
	RightTrack->setThrottle(Throw);

	//TODO prevent from the double speed due to the dual control

	return;
}

void UTankMovementComponent::SetTracks(UTankTrack * LeftTracToSet, UTankTrack * RightTrackToSet)
{
	if ((!LeftTracToSet) || (!RightTrackToSet)) { return; }
	LeftTrack = LeftTracToSet;
	RightTrack = RightTrackToSet;
}
