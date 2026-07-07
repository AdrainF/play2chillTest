// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "P2C_AbilitySystemComponent.generated.h"

class UP2C_AbilityDataAsset;

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
	void GrantAbility(FGameplayTag AbilityTag,  UP2C_AbilityDataAsset* DA);
	// Activates an ability based on its tag
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void ActivateAbility(const FGameplayTag AbilityTag);
	// Adds an active tag to the component's active tags
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void AddActiveTag(FGameplayTag Tag) { ActiveTags.AddTag(Tag); }
	//UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	UFUNCTION(BlueprintCallable, Category = "P2C|Abilities")
	void RemoveActiveTag(FGameplayTag Tag) { ActiveTags.RemoveTag(Tag); }
	
private:
	
	UPROPERTY()
	TMap<FGameplayTag, UP2C_AbilityDataAsset*> ActiveAbilities;

	UPROPERTY()
	FGameplayTagContainer ActiveTags;
	
	
};
