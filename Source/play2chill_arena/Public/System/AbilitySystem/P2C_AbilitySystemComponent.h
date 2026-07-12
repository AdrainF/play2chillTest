// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "P2C_AbilitySystemComponent.generated.h"

class UP2C_AbilityDataAsset;
class UP2C_AbilityBase;

USTRUCT(BlueprintType)
struct FAbilitySlot
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGameplayTag Tag;
 
	UPROPERTY()
	UP2C_AbilityDataAsset* Data = nullptr;
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY2CHILL_ARENA_API UP2C_AbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY() 

public:	
	// Sets default values for this component's properties
	UP2C_AbilitySystemComponent();

public:
	// Called to check if an ability can be activated based on its data asset
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	bool CanActivateAbility(const UP2C_AbilityDataAsset* DA) const;
	// Grants an ability to the component based on its tag and data asset
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void GrantAbility(UP2C_AbilityDataAsset* DA);
	// Activates an ability based on its tag
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void ActivateAbility(const FGameplayTag AbilityTag);
	// Adds an active tag to the component's active tags
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void AddActiveTag(FGameplayTag Tag) { ActiveTags.AddTag(Tag); }
	//UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void RemoveActiveTag(FGameplayTag Tag) { ActiveTags.RemoveTag(Tag); }

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RequestActivateAbility(FGameplayTag AbilityTag);
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RequestGrantAbility(UP2C_AbilityDataAsset* DA);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void NotifyAbilityFinished(UP2C_AbilityBase* Ability);
private:
	// Map of active abilities, keyed by their gameplay tags
	UPROPERTY(Replicated)
	TArray<FAbilitySlot> ReplicatedAbilities;
	// Container of active gameplay tags that affect the component's abilities
	UPROPERTY(Replicated)
	FGameplayTagContainer ActiveTags;
protected:

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ActivateAbility(FGameplayTag AbilityTag);
 
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_GrantAbility(UP2C_AbilityDataAsset* DA);
	
	UPROPERTY(Replicated)
	TArray<UP2C_AbilityBase*> RunningAbilities;
	
};
