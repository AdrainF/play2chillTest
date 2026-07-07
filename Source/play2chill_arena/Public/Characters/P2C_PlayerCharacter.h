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
/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_PlayerCharacter : public AP2C_CharacterBase
{
	GENERATED_BODY()

public:
	AP2C_PlayerCharacter();

	UPROPERTY(Blueprintable, EditAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent>  CameraBoom;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TObjectPtr<UP2C_AbilitySystemComponent> AbilitySystemComp;

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UP2C_InputConfig> InputConfig;
 
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

protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
