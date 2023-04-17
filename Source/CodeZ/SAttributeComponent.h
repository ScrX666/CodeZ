// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"
//我理解的是，声明了一个Type叫FOnHealthChanged，它是一个DELEGATE，有四个参数，有点像typedef？
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,float,health,float,delta,AActor*,instigetorActor,USAttributeComponent*,ownComp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEZ_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();
	bool TakeDamage(float damage);
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
protected:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly,Category="Attribute")
	float Health;
	
	

		
};
