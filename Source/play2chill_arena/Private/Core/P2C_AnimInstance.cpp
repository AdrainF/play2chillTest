// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/P2C_AnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UP2C_AnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	APawn* Owner = TryGetPawnOwner();
	if (!Owner) return;
	
	FVector Velocity = Owner->GetVelocity();
	GroundSpeed = Velocity.Size2D();
	
	if (GroundSpeed > 3.0f)
	{
		Direction = UKismetAnimationLibrary:: CalculateDirection(Velocity, Owner->GetActorRotation());
	}
	else
	{
		Direction = 0.0f;
	}
	if (const ACharacter* CharOwner = Cast<ACharacter>(Owner))
	{
		if (UCharacterMovementComponent* MoveComp = CharOwner->GetCharacterMovement())
		{
			bIsFalling = MoveComp->IsFalling();
		}
	}
}
