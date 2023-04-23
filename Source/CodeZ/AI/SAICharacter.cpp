// Fill out your copyright notice in the Description page of Project Settings.


#include "SAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
	PawnSensingComponent=CreateDefaultSubobject<UPawnSensingComponent>("SeePawnComponent");
}

void ASAICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* AaiController = Cast<AAIController>(GetController());
	if(AaiController)
	{
		UBlackboardComponent* BlackboardComponent = AaiController->GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject("TargetActor",Pawn);
	}
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComponent->OnSeePawn.AddDynamic(this,&ASAICharacter::OnSeePawn);
}

