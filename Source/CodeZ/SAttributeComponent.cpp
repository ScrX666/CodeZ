// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
}

bool USAttributeComponent::IsAlive()
{
	return Health>0.0f;
}


bool USAttributeComponent::TakeDamage(float damage)
{
	Health += damage;
	//multicast中的方法
	OnHealthChanged.Broadcast(Health,damage,nullptr,this);
	return true;
}




