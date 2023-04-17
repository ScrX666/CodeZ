// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetDummyActor.h"
#include "SAttributeComponent.h"

// Sets default values
ASTargetDummyActor::ASTargetDummyActor()
{
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	RootComponent = StaticMeshComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	AttributeComponent->OnHealthChanged.AddDynamic(this,&ASTargetDummyActor::OnHitActor);
}

void ASTargetDummyActor::OnHitActor(float health, float delta, AActor* instigetorActor, USAttributeComponent* ownComp)
{
	if(delta < 0)
	{
		StaticMeshComponent->SetScalarParameterValueOnMaterials("TimeOnHit",GetWorld()->TimeSeconds);
	}
}


