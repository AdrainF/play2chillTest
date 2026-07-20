// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/P2C_ANS_WeaponTrace.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_AttributionComponent.h"
#include "Items/Data/MyP2C_WeaponDataAsset.h"
#include "Items/Weapons/P2C_WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"


void UP2C_ANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner  || !Owner->HasAuthority()) { return; }
		
		if (AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(MeshComp->GetOwner()))
		{
			if (Char->EquippedWeapon)
			{
				Char->EquippedWeapon->SetTraceWeapon(true);
				UE_LOG(LogTemp, Error, TEXT("!!! NOTIFY BEGIN !!! Cleaning Weapon: %s (Address: %p)"), 
				*Char->EquippedWeapon->GetName(), Char->EquippedWeapon.Get());
			}
		}
	
}

void UP2C_ANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner  || !Owner->HasAuthority()) { return; }
		
	if (AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(MeshComp->GetOwner()))
	{
		if (Char->EquippedWeapon)
		{
			Char->EquippedWeapon->SetTraceWeapon(false);
		}
	}
}
