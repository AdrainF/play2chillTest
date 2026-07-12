// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/P2C_ANS_WeaponTrace.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Items/Weapons/P2C_WeaponBase.h"

void UP2C_ANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(MeshComp->GetOwner()))
	{
		if (Char->EquippedWeapon)
		{
			Char->EquippedWeapon->StartTrace();
		}
			
	}
	
}

void UP2C_ANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(MeshComp->GetOwner()))
	{
		if (Char->EquippedWeapon)
		{
			Char->EquippedWeapon->EndTrace();
		}
	}
}
