// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "P2C_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
 
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;
 
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Direction;
};
