// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemsActor.h"

void AItemsActor::Interact_Implementation(APawn* interactPawn)
{
	
}

// Sets default values
AItemsActor::AItemsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
	SecondMesh=CreateDefaultSubobject<UStaticMeshComponent>("SecondMesh");
	SecondMesh->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AItemsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

