// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "P2C_AbilityBase.generated.h"

/**
 * 
 */
class UP2C_AbilitySystemComponent;
class UP2C_AbilityDataAsset;
class ACharacter;

UCLASS(Abstract, Blueprintable)
class PLAY2CHILL_ARENA_API UP2C_AbilityBase : public UObject
{
	GENERATED_BODY()

public:
	// Initializes the ability with the owning component and ability data
	virtual void Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA);
	// Activates the ability, calling the Blueprint-implementable event OnActivate
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void FinishAbility();
	// Returns the character that owns this ability, if any
	UFUNCTION(BlueprintPure, Category = "P2C|Ability")
	AP2C_PlayerCharacter* GetP2CCharacter() const;
protected:
	// Blueprint-implementable event that is called when the ability is activated
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Activate"))
	void K2_OnActivate();
	
	// Reference to the owning ability system component
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UP2C_AbilitySystemComponent> OwningComp;
	// Reference to the ability data asset that defines this ability's properties and behavior
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<const UP2C_AbilityDataAsset> AbilityData;


};
