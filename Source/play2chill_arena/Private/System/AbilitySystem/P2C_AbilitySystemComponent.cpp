// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/P2C_AbilitySystemComponent.h"

#include "Components/P2C_AttributionComponent.h"
#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"
#include "System/AbilitySystem/Abilities/Data/P2C_AbilityDataAsset.h"

// Sets default values for this component's properties
UP2C_AbilitySystemComponent::UP2C_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

bool UP2C_AbilitySystemComponent::CanActivateAbility(const UP2C_AbilityDataAsset* DA) const
{
	if (!DA) return false;
	UP2C_AttributionComponent * AttrComp = Cast<UP2C_AttributionComponent>(
		GetOwner()->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));
	// Check if the ability is granted
	if (FMath::Abs(DA->StaminaCost)>AttrComp->GetStamina())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough stamina"), *DA->AbilityTag.ToString());
		return false;
	}
	
	if (ActiveTags.HasAny(DA->AbilityBlockTags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability with tag %s is blocked"), *DA->AbilityTag.ToString());
		return false;
	}
	return true;
}

void UP2C_AbilitySystemComponent::GrantAbility(UP2C_AbilityDataAsset* DA)
{
	if (!DA) return;

	// Check if the ability is already granted

	for (auto& RepAbilityTag : ReplicatedAbilities)
		if (RepAbilityTag.Tag == DA->AbilityTag)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability with tag %s is already granted."), *DA->AbilityTag.ToString());
			return;
		}


	FAbilitySlot AbilityToAdd = FAbilitySlot(DA->AbilityTag, DA);
	ReplicatedAbilities.Add(AbilityToAdd);
}

void UP2C_AbilitySystemComponent::RevokeAbility(UP2C_AbilityDataAsset* DA)
{
	if (!DA) return;

	for (int32 Index = 0; Index <= ReplicatedAbilities.Num(); Index++)
		if (ReplicatedAbilities[Index].Tag == DA->AbilityTag)
		{
			ReplicatedAbilities.RemoveAt(Index);
		}
	
}

void UP2C_AbilitySystemComponent::ActivateAbility(const FGameplayTag AbilityTag)
{
	UP2C_AbilityDataAsset* FoundDA = nullptr;
	for (auto& Elem : ReplicatedAbilities)
	{
		FGameplayTag& GrantedTag = Elem.Tag;
		if (GrantedTag.MatchesTag(AbilityTag))
		{
			FoundDA = Elem.Data;
			break;
		}
	}
	if (!FoundDA)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ability found matching tag hierarchy for: %s"), *AbilityTag.ToString());
		return;
	}

	if (!CanActivateAbility(FoundDA)) { return; }
	// Create an instance of the ability class
	UP2C_AbilityBase* AbilityToRun = NewObject<UP2C_AbilityBase>(this, FoundDA->AbilityClass);
	if (AbilityToRun)
	{
		UP2C_AttributionComponent * AttrComp = Cast<UP2C_AttributionComponent>(
		GetOwner()->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));
		
			AttrComp->Server_ApplyStaminaChange(FoundDA->StaminaCost);
	
		
		RunningAbilities.Add(AbilityToRun);
		AbilityToRun->Internal_StartAbility(this, FoundDA);
		UE_LOG(LogTemp, Warning, TEXT("Run ability: %s"), *AbilityToRun->GetName());
	}
}

void UP2C_AbilitySystemComponent::RequestActivateAbility(FGameplayTag AbilityTag)
{
	if (!GetOwner()->HasAuthority())
	{
		Server_ActivateAbility(AbilityTag);
	}
	else
	{
		ActivateAbility(AbilityTag);
	}
}

void UP2C_AbilitySystemComponent::RequestGrantAbility(UP2C_AbilityDataAsset* DA)
{
	if (!DA) return;
	if (!GetOwner()->HasAuthority())
	{
		Server_GrantAbility(DA);
	}
	else
	{
		GrantAbility(DA);
	}
}

void UP2C_AbilitySystemComponent::RequestRevokeAbility(UP2C_AbilityDataAsset* DA)
{
	if (!DA) return;
	if (!GetOwner()->HasAuthority())
	{
		Server_RevokeAbility(DA);
	}
	else
	{
		RequestRevokeAbility(DA);
	}
}


void UP2C_AbilitySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UP2C_AbilitySystemComponent, ReplicatedAbilities);
	DOREPLIFETIME(UP2C_AbilitySystemComponent, ActiveTags);
	DOREPLIFETIME(UP2C_AbilitySystemComponent, RunningAbilities);
}

void UP2C_AbilitySystemComponent::NotifyAbilityFinished(UP2C_AbilityBase* Ability)
{
	if (Ability)
	{
		RunningAbilities.Remove(Ability);
	}
}

void UP2C_AbilitySystemComponent::Server_RevokeAbility_Implementation(UP2C_AbilityDataAsset* DA)
{
	if (DA)
	{
		RevokeAbility(DA);
	}
}

bool UP2C_AbilitySystemComponent::Server_RevokeAbility_Validate(UP2C_AbilityDataAsset* DA)
{
	return true;
}


void UP2C_AbilitySystemComponent::Server_GrantAbility_Implementation(UP2C_AbilityDataAsset* DA)
{
	if (DA)
	{
		GrantAbility(DA);
	}
}

bool UP2C_AbilitySystemComponent::Server_GrantAbility_Validate(UP2C_AbilityDataAsset* DA)
{
	return true;
}

void UP2C_AbilitySystemComponent::Server_ActivateAbility_Implementation(FGameplayTag AbilityTag)
{
	ActivateAbility(AbilityTag);
}

bool UP2C_AbilitySystemComponent::Server_ActivateAbility_Validate(FGameplayTag AbilityTag)
{
	return true;
}
