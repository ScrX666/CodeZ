// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBaseActor.h"
#include "GameFramework/Actor.h"
#include "SMagicDashActor.generated.h"

UCLASS()
class CODEZ_API ASMagicDashActor : public ASProjectileBaseActor
{
	GENERATED_BODY()
	
public:	

	ASMagicDashActor();

protected:

	FTimerHandle TimerHandle_DetonateDelay;
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float DetonateDelay;
	UPROPERTY(EditDefaultsOnly,Category="Teleport")
	float TeleportDelay;
	
	virtual void BeginPlay() override;
	virtual void Explode_Implementation() override;
	void TeleportInstigator();


};
