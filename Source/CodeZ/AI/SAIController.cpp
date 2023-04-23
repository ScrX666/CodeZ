// Fill out your copyright notice in the Description page of Project Settings.


#include "SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(AIRangedBehaviorTree);
	// APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this,0);
	// GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
}
