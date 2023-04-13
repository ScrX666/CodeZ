//Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "ItemsActor.generated.h"

UCLASS()
class CODEZ_API AItemsActor : public AActor ,public ISGameplayInterface
{
	GENERATED_BODY()
private:
	virtual void Interact_Implementation(APawn* interactPawn) override;
	
public:	
	// Sets default values for this actor's properties
	AItemsActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UStaticMeshComponent* SecondMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
