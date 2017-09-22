// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"




void UTankMovementComponent::IntendMoveForward(float Throw) {


	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->setThrottle(Throw);
	RightTrack->setThrottle(Throw);

	//TODO prevent from the double speed due to the dual control

	return;
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if (!ensure(LeftTrack) || !ensure(RightTrack)) { return; }
	LeftTrack->setThrottle(Throw);
	RightTrack->setThrottle(-Throw);

	//TODO prevent from the double speed due to the dual control

	return;

}

void UTankMovementComponent::SetTracks(UTankTrack * LeftTracToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTracToSet) || !ensure(RightTrackToSet)) { return; }
	LeftTrack = LeftTracToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super() as we re replacing the mehod here
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct( TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	IntendMoveRight(RightThrow);

}
