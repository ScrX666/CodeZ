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
	PlayerInputComponent->BindAction("Attack",IE_Pressed,this,&ASCharacter::PrimaryAttack_TimerElapsed);
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
		
	PlayAnimMontage(ProjectileAttackAnim,2.0f,"start");

	//Delay spawn location by timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack,MontageDelayTime);
}

void ASCharacter::PrimaryAttack() 
{
	FVector MagicLocaton = GetMesh()->GetSocketLocation("S_R_Magic");
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner();
	
	FVector EyeStart;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeStart,EyeRotation);
	FVector End = EyeStart +(EyeRotation.Vector() * 1000);
	FRotator PlayerRotator = FRotationMatrix::MakeFromX(End - MagicLocaton).Rotator();
	
	//Debug单次射线检测
	FHitResult OutHit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(OutHit,EyeStart,End,ObjectQueryParams);
	FColor DebugLineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(),EyeStart,End,DebugLineColor,false,2.0f,2.0f,0.0f);


	FTransform ProjectileTransform = FTransform(PlayerRotator,MagicLocaton);
	
	FActorSpawnParameters ProjectileParams;
	ProjectileParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ProjectileParams.Instigator = this;	//投出一个Instigator，蓝图中判断是否与自身的Instigator相撞
	GetWorld()->SpawnActor<AActor>(ProjectileClass,ProjectileTransform,ProjectileParams);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}

