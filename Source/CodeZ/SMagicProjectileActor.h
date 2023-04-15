// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectileActor.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class USphereComponent;

UCLASS()
class CODEZ_API ASMagicProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnActoroverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	ASMagicProjectileActor();
	

	
protected:
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
	
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	USphereComponent* SphereComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
