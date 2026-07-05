// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/P2C_CharacterBase.h"
#include "P2C_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
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
	USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	UCameraComponent* FollowCamera;
	
};
