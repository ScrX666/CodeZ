// Fill out your copyright notice in the Description page of Project Settings.


#include "SAIController.h"



void ASAIController::BeginPlay()
{
	Super::BeginPlay();
	if(ensureMsgf(AIRangedBehaviorTree, TEXT("AI: RangedBehavior is a nullptr,check if you had assin it in AIContoller.")))
	{
		RunBehaviorTree(AIRangedBehaviorTree);
	}
	

}
