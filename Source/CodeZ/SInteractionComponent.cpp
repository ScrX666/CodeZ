// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner();
	
	FVector EyeStart;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeStart,EyeRotation);
	FVector End = EyeStart +(EyeRotation.Vector() * 1000);
	/*
		//单次射线检测
		FHitResult OutHit;
		
		//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(OutHit,EyeStart,End,ObjectQueryParams);
	*/
	//多次射出圆形检测
	float Radius = 30.0f;
	TArray<FHitResult> OutHit;
	FCollisionShape CircleShape;
	CircleShape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(OutHit,EyeStart,End,FQuat::Identity,ObjectQueryParams,CircleShape);
	//画出Debug线，正确命中为绿色，未命中红色
	FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for(FHitResult Hit : OutHit)
	{
		AActor* HitActor = Hit.GetActor();
	
		if(HitActor)
		{
			//类型转化，actor -》 pawn
			APawn* MyPawn = Cast<APawn>(MyOwner);
			if(HitActor->Implements<USGameplayInterface>())
			{
				ISGameplayInterface::Execute_Interact(HitActor,MyPawn);
			}
		}
		DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,DebugLineColor,false,2.0f,2.0f,0.0f);
		//防止圆形重叠两个物体同时打开，一次按键在找到一个Hit后跳出循环不再交互
		break;
	}
		
		DrawDebugLine(GetWorld(),EyeStart,End,DebugLineColor,false,2.0f,2.0f,0.0f);
	
}
