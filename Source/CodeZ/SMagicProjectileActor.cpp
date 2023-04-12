// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectileActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectileActor::ASMagicProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent=CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName("Projectile");
	ParticleSystemComponent=CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	ParticleSystemComponent->SetupAttachment(SphereComponent);
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASMagicProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMagicProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

