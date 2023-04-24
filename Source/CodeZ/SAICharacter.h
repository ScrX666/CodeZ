// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "SAICharacter.generated.h"

UCLASS()
class CODEZ_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();
protected:
	UPROPERTY(VisibleAnywhere,Category="Components")
	UPawnSensingComponent* PawnSensingComponent;
	
public:
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	virtual void PostInitializeComponents() override;

};
