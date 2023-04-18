// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBaseActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASProjectileBaseActor::ASProjectileBaseActor()
{
	SphereComponent=CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName("Projectile");
	SphereComponent->OnComponentHit.AddDynamic(this,&ASProjectileBaseActor::OnHitActor);
	
	EffectComponent=CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	EffectComponent->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	

}

void ASProjectileBaseActor::OnHitActor(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp,
	FVector normalImpulse, const FHitResult& hitResult)
{
	//撞到其他物体触发爆炸特效
	Explode();
}

void ASProjectileBaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASProjectileBaseActor::Explode_Implementation()
{
	if(ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVfxComponent,GetActorLocation(),GetActorRotation());
		Destroy();
	}
}







