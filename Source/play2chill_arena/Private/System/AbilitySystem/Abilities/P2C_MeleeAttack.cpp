// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/Abilities/P2C_MeleeAttack.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_NetworkComponent.h"
#include "Items/Weapons/P2C_WeaponBase.h"

UP2C_MeleeAttack::UP2C_MeleeAttack()
{
}

void UP2C_MeleeAttack::PerformMeleeAttack()
{

	AP2C_PlayerCharacter* P2CCharacter = GetP2CCharacter();

	UAnimInstance* AnimInstance = P2CCharacter->GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;
	
	if (AnimInstance->Montage_IsPlaying(MontageToPlay))
	{
		return; 
	}
	
	if (P2CCharacter && MontageToPlay)
	{
		P2CCharacter->NetworkComp->Request_PlayAttack(MontageToPlay);
		
		
		float Duration = P2CCharacter->PlayAnimMontage(MontageToPlay);
		//float Duration = MontageToPlay->GetPlayLength();
		if (Duration > 0.0f)
		{
			
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &UP2C_MeleeAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				FOnMontageBlendingOutStarted BlendDelegate;
				BlendDelegate.BindUObject(this, &UP2C_MeleeAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendDelegate, MontageToPlay);
			}
			
		}
		else
		{
			
			FinishAbility();
		}
	}
}

void UP2C_MeleeAttack::Internal_StartAbility(UP2C_AbilitySystemComponent* InComp,
                                                  const UP2C_AbilityDataAsset* InDA)
{
	Super::Internal_StartAbility(InComp, InDA);
	
	PerformMeleeAttack();
}


void UP2C_MeleeAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	AP2C_PlayerCharacter* P2CCharacter = GetP2CCharacter();
	P2CCharacter->EquippedWeapon->Request_ClearHitActors();
	FinishAbility();
}

