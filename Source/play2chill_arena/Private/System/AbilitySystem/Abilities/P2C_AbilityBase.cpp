// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"

#include "GameFramework/Character.h"
#include "System/AbilitySystem/P2C_AbilitySystemComponent.h"
#include "System/AbilitySystem/Abilities/Data/P2C_AbilityDataAsset.h"

void UP2C_AbilityBase::Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA)
{
	OwningComp = InComp;
	AbilityData = InDA;
 
	if (OwningComp && AbilityData)
	{
		//Add the ability tag to the owning component when the ability starts
		OwningComp->AddActiveTag(AbilityData->AbilityTag);
	}
 
	K2_OnActivate();
}

void UP2C_AbilityBase::FinishAbility()
{
	if (OwningComp && AbilityData)
	{
		//Remove the ability tag from the owning component when the ability finishes
		OwningComp->RemoveActiveTag(AbilityData->AbilityTag);
	}
 
	// Mark the ability object for garbage collection
	MarkAsGarbage();
}

ACharacter* UP2C_AbilityBase::GetP2CCharacter() const
{
	if (!OwningComp){ return nullptr; }
	return Cast<ACharacter>(OwningComp->GetOwner());
}
