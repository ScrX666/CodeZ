// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USAttributeComponent;
class USInteractionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CODEZ_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Dash;
	FTimerHandle TimerHandle_BlackHole;
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Attribute")
	USAttributeComponent* AttributeComponent;
	UPROPERTY(EditAnywhere,Category="Attack")
	float MontageDelayTime = 0.25f;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent;
	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* ProjectileAttackAnim;
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> DashProjectileClass;
	UPROPERTY(EditAnywhere,Category="Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;
	
	void MoveForward(float value);
	void MoveRight(float value);
	
	void PrimaryAttack();
	void PrimaryAttack_TimerElapsed();
	
	void DashAttack();
	void DashAttack_TimerElapsed();

	void BlackHoleAttack();
	void BlackHoleAttack_TimerElapsed();
	
	void PrimaryInteract();
	void OnHealthChanged(float delta, float health,AActor* instigetorActor,USAttributeComponent* ownComp);
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
};
