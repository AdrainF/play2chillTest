// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/P2C_AttributionComponent.h"
#include "Components/P2C_InteractionComponent.h"
#include "Components/P2C_NetworkComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Input/P2C_EnhancedInputComponent.h"
#include "System/P2C_GameplayTags.h"
#include "System/AbilitySystem/P2C_AbilitySystemComponent.h"

AP2C_PlayerCharacter::AP2C_PlayerCharacter()
{
	CameraBoom= CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera= CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	AbilitySystemComp=CreateDefaultSubobject<UP2C_AbilitySystemComponent>(TEXT("AbilitySystemComp"));
	InteractionComp=CreateDefaultSubobject<UP2C_InteractionComponent>(TEXT("InteractionComp"));

	NetworkComp= CreateDefaultSubobject<UP2C_NetworkComponent>(TEXT("NetworComponent"));

	NetPriority = 3.0f;
}

void AP2C_PlayerCharacter::Die(UP2C_AttributionComponent* AttriComp, AActor* InstigatorActor, AActor* DamageActor)
{
	if (!HasAuthority()) return;
 
	// Notify the GameMode that we need to respawn
	NetworkComp->Server_RequestRespawn();
	if (DeathMontage)
	{
		NetworkComp->Server_PlayAttack(DeathMontage);
	}
	
	FTimerDelegate DeathDelegate;
	DeathDelegate.BindUObject(this, &AP2C_PlayerCharacter::Death_TimeElaps);
	// Destroy the old body
	GetWorldTimerManager().SetTimer(DeathTimer,DeathDelegate,2.0f,false);
}

void AP2C_PlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// Calculate forward and right movement directions
	const FVector Forward = ControlRot.Vector();
	const FVector Right = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
	
}

void AP2C_PlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	
}

void AP2C_PlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AP2C_PlayerCharacter::Input_Attack(const FInputActionValue& InputActionValue)
{
}

void AP2C_PlayerCharacter::Input_Interaction(const FInputActionValue& InputActionValue)
{
	InteractionComp->RequestInteract();
}

void AP2C_PlayerCharacter::Death_TimeElaps()
{
	Destroy();
}

void AP2C_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!AttrComp->OnDeath.IsAlreadyBound(this, &AP2C_PlayerCharacter::Die))
	{
		AttrComp->OnDeath.AddDynamic(this, &AP2C_PlayerCharacter::Die);
	}
}

void AP2C_PlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AP2C_PlayerCharacter, EquippedWeapon);
}

void AP2C_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	UP2C_EnhancedInputComponent* EnhancedInputComp = Cast<UP2C_EnhancedInputComponent>(PlayerInputComponent);
 
	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(EnhancedInputComp);
 
	const FP2C_GameplayTags& GameplayTags = FP2C_GameplayTags::Get();
 
	//Bind Input actions by tag
	EnhancedInputComp->BindActionByTag(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &AP2C_PlayerCharacter::Input_Move);
	EnhancedInputComp->BindActionByTag(InputConfig, GameplayTags.InputTag_Look, ETriggerEvent::Triggered, this, &AP2C_PlayerCharacter::Input_Look);
	EnhancedInputComp->BindActionByTag(InputConfig, GameplayTags.InputTag_Jump, ETriggerEvent::Triggered, this, &AP2C_PlayerCharacter::Input_Jump);
	EnhancedInputComp->BindActionByTag(InputConfig, GameplayTags.InputTag_Attack, ETriggerEvent::Triggered, this, &AP2C_PlayerCharacter::Input_Attack);
	EnhancedInputComp->BindActionByTag(InputConfig, GameplayTags.InputTag_Interact, ETriggerEvent::Triggered, this, &AP2C_PlayerCharacter::Input_Interaction);

}
