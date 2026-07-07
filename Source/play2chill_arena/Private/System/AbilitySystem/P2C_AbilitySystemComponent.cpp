// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/P2C_AbilitySystemComponent.h"

#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"
#include "System/AbilitySystem/Abilities/Data/P2C_AbilityDataAsset.h"

// Sets default values for this component's properties
UP2C_AbilitySystemComponent::UP2C_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UP2C_AbilitySystemComponent::CanActivateAbility(const UP2C_AbilityDataAsset* DA) const 
{
	if (!DA) return false;
	// Check if the ability is granted
	if (ActiveTags.HasAny(DA->AbilityBlockTags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability with tag %s is blocked"), *DA->AbilityTag.ToString() );
		return false;
	}
	return true;
}

void UP2C_AbilitySystemComponent::GrantAbility(FGameplayTag AbilityTag, UP2C_AbilityDataAsset* DA)
{
	if (!DA) return;
	// Check if the ability is already granted
	if (ActiveAbilities.Contains(AbilityTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability with tag %s is already granted."), *AbilityTag.ToString());
		return;
	}
	
	ActiveAbilities.Add(AbilityTag, DA);
}

void UP2C_AbilitySystemComponent::ActivateAbility(const FGameplayTag AbilityTag)
{
	if (!ActiveAbilities.Contains(AbilityTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability with tag %s is not granted."), *AbilityTag.ToString());
		return;	
	}
	// Find the ability data asset associated with the tag
	UP2C_AbilityDataAsset** FoundDA = ActiveAbilities.Find(AbilityTag);
	if (!FoundDA) return;
	const UP2C_AbilityDataAsset* DA = *FoundDA;
	
	// Create an instance of the ability class
	UP2C_AbilityBase* AbilityToRun = NewObject<UP2C_AbilityBase>(this, DA->AbilityClass);

	if (AbilityToRun)
	{
		AbilityToRun->Internal_StartAbility(this, DA);
	}
	
}




