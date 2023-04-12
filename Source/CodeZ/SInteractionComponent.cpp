// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

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
	
	FHitResult OutHit;
	//单次射线检测
	GetWorld()->LineTraceSingleByObjectType(OutHit,EyeStart,End,ObjectQueryParams);
}
