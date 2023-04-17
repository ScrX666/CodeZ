// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummyActor.generated.h"

class USAttributeComponent;
UCLASS()
class CODEZ_API ASTargetDummyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummyActor();
protected:
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
public:
	//OnHealthChanged()
	UFUNCTION()
	void OnHitActor(float health,float delta,AActor* instigetorActor,USAttributeComponent* ownComp);
};
