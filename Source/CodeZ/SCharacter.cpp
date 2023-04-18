// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Set sub relationship
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	
	//Init BP
	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Up",this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed,this,&ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Dash",IE_Pressed,this,&ASCharacter::DashAttack);
	PlayerInputComponent->BindAction("PrimaryInteract",IE_Pressed,this,&ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	const FVector RightRotator = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightRotator,value);
}
void ASCharacter::PrimaryAttack_TimerElapsed()
{
	SpawnProjectile(ProjectileClass);	
}

void ASCharacter::PrimaryAttack() 
{
	PlayAnimMontage(ProjectileAttackAnim,2.0f,"start");

	//Delay spawn location by timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimerElapsed,MontageDelayTime);
	
}

void ASCharacter::DashAttack()
{
	PlayAnimMontage(ProjectileAttackAnim,2.0f,"start");

	//Delay spawn location by timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Dash,this,&ASCharacter::DashAttack_TimerElapsed,MontageDelayTime);
}
void ASCharacter::DashAttack_TimerElapsed()
{
	SpawnProjectile(DashProjectileClass);	
}


void ASCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if(ensure(ClassToSpawn))
	{
		FVector MagicLocaton = GetMesh()->GetSocketLocation("S_R_Magic");
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = CameraComp->GetComponentLocation() + (CameraComp->GetComponentRotation().Vector() * 5000);

		FHitResult Hit;
		
		 //1 单次射线检测
		 //bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit,TraceStart,TraceEnd,ObjectQueryParams);

		//2 扫描检测
		//如果撞到上面ObjectQueryParams标记的几种类型返回true
		bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit,TraceStart,TraceEnd,FQuat::Identity,ObjectQueryParams,Shape,Params);
		
		if(bBlockingHit)
		{
			//将TraceEnd改写为撞击点
			TraceEnd = Hit.ImpactPoint;
		}
		//Debug
		FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(),TraceStart,TraceEnd,DebugLineColor,false,2.0f,2.0f,0.0f);
		
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TraceEnd - MagicLocaton).Rotator();;

		FTransform ProjectileTM = FTransform(ProjectileRotation,MagicLocaton);
		GetWorld()->SpawnActor<AActor>(ProjectileClass,ProjectileTM,SpawnParameters);
		
	}
	
 }

	void ASCharacter::PrimaryInteract()
	{
		InteractionComponent->PrimaryInteract();
	}