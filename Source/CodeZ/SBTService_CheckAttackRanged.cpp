// Fill out your copyright notice in the Description page of Project Settings.


#include "SBTService_CheckAttackRanged.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void USBTService_CheckAttackRanged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//check distance between AI pawn and target actor
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComponent))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if(TargetActor)
		{
			AAIController* AIController = OwnerComp.GetAIOwner();
			if(ensure(AIController))
			{
				APawn* AIPawn = AIController->GetPawn();
				if(ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
					
					bool bIsInArea = DistanceTo < AreaDistance;
					bool bHasLos = false;
					if(bIsInArea)
					{
						//检测TargetActor是否在视线内
						bHasLos = AIController->LineOfSightTo(TargetActor);
					}
					
					BlackboardComponent->SetValueAsBool(InAreaSeletor.SelectedKeyName,(bHasLos && bIsInArea));//同时满足
				}
			}
		}
	}
}
