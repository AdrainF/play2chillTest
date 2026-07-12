// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/P2C_CharacterBase.h"
#include "P2C_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UP2C_InputConfig;
struct FInputActionValue;
class UP2C_AbilitySystemComponent;
class UP2C_InteractionComponent;
class AP2C_WeaponBase;
class UP2C_NetworkComponent;
/**
 * 
 */

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_PlayerCharacter : public AP2C_CharacterBase
{
	GENERATED_BODY()

public:
	AP2C_PlayerCharacter();

	UPROPERTY()
	int32 CurrentMeleeComboIndex;
	UPROPERTY()
	bool bSaveAttackInput=false;
	
	UPROPERTY(Blueprintable, EditAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent>  CameraBoom;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(Replicated,BlueprintReadOnly)
	TObjectPtr<AP2C_WeaponBase> EquippedWeapon;
	
	// Ability System Component for this character
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TObjectPtr<UP2C_AbilitySystemComponent> AbilitySystemComp;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UP2C_InputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UP2C_InteractionComponent> InteractionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	TObjectPtr<UP2C_NetworkComponent> NetworkComp;

	
	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);
 
	/** Handles mouse look */
	void Input_Look(const FInputActionValue& InputActionValue);
 
	/** Handles Jumping */
	void Input_Jump(const FInputActionValue& InputActionValue);
 
	/** Handles Melee Attack */
	void Input_AttackMelee(const FInputActionValue& InputActionValue);

	/** Handles Ranged Attack */
	void Input_AttackRanged(const FInputActionValue& InputActionValue);

	void Input_Interaction(const FInputActionValue& InputActionValue);

protected:

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
