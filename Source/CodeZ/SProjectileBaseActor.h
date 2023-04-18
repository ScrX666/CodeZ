// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBaseActor.generated.h"
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class CODEZ_API ASProjectileBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASProjectileBaseActor();

protected:
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UParticleSystemComponent* EffectComponent;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UParticleSystemComponent* ImpactVfxComponent;

	UFUNCTION()
	void OnHitActor(UPrimitiveComponent* hitComp,AActor* otherActor,UPrimitiveComponent* otherComp,FVector normalImpulse, const FHitResult& hitResult);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Explode();
	virtual void PostInitializeComponents() override;
};
