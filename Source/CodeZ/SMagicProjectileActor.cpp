// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectileActor.h"

#include "SAttributeComponent.h"
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
	//当Sphere组件与其他物体重叠时，调用OnActoroverlap函数
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ASMagicProjectileActor::OnActoroverlap);
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
void ASMagicProjectileActor::OnActoroverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//检查是否与其他Actor重叠
	if(OtherActor)
	{
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OtherActor->FindComponentByClass(USAttributeComponent::StaticClass()));
		//再次检查是否撞到的物体有Attribute组件
		if(AttributeComponent)
		{
			//攻击扣血
			AttributeComponent->TakeDamage(-20.0f);
		}
	}
}
