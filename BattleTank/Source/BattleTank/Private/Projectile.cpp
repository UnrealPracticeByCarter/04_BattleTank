// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("launch blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



void AProjectile::Launchprojectile(float speed) {

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	ProjectileMovement->Activate();
	


}