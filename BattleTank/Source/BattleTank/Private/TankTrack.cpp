// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "engine/World.h"





void UTankTrack::setThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,+1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit); // this seems will be set to be called every frame.
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	//Dirve the Track
	DriveTrack();
	//Apply Sideways Force
	ApplaySidewaysForce();
	//reset the throttle
	CurrentThrottle = 0;

}





void UTankTrack::ApplaySidewaysForce()
{
	//caculate the slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//work out the required acceleration this frame to correct
	//just get the DeltaTime From the world.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	//Calculate and apply sideway 
	// inorder to get the mass, we need to cast the Tank to the UStaticMeshComponent  
	//directly from the getRootComponent will reture a USceneComponent. and it did not contain the physical simualtion.
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two Tracks
																			   //auto CorrectionForce
	TankRoot->AddForce(CorrectionForce);
}
