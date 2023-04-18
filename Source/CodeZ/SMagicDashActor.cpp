// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicDashActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicDashActor::ASMagicDashActor()
{
	DetonateDelay = 0.2f;
	TeleportDelay = 0.2f;

	ProjectileMovementComponent->InitialSpeed = 5000.0f;
}

void ASMagicDashActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_DetonateDelay,this,&ASMagicDashActor::Explode,DetonateDelay);
	// InOutHandle 是我们要设置的计时器
	// UserClass 调用timer函数的object
	// InTimerMethod timer会重复执行的方法
	// InRate 调用频率，例如填0.5f的话，那么InTimerMethod就会每隔0.5f调用一次
	// InbLoop 是否循环，如果是false的那么方法只会执行一次
	// InFirstDelay 第一次调用之前延时的时间，例如5.0f，那么过5秒后，方法才执行，然后才根据InRate 正常调用
}

void ASMagicDashActor::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DetonateDelay);
	UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVfxComponent,GetActorLocation(),GetActorRotation());
	//初始化碰撞之后的状态
	EffectComponent->DeactivateSystem();
	ProjectileMovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);
	
	FTimerHandle TimerHandle_TeleportDelay;
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportDelay,this,&ASMagicDashActor::TeleportInstigator,TeleportDelay);
	
}

void ASMagicDashActor::TeleportInstigator()
{
	AActor* TeleportInstigator = GetInstigator();
	if(ensure(TeleportInstigator))
	{
		TeleportInstigator->TeleportTo(GetActorLocation(),TeleportInstigator->GetActorRotation(),false,false);
	}
	Destroy();
}


