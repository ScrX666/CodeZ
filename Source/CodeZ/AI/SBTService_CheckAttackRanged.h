// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckAttackRanged.generated.h"

/**
 * 
 */
UCLASS()
class CODEZ_API USBTService_CheckAttackRanged : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector InAreaSeletor;
	UPROPERTY(EditAnywhere,Category="AI")
	float AreaDistance = 1000.0f;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
