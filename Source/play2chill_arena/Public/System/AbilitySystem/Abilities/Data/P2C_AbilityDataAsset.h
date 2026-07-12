// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "P2C_AbilityDataAsset.generated.h"




UCLASS()
class PLAY2CHILL_ARENA_API UP2C_AbilityDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// The class of the ability that this data asset represents
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<class UP2C_AbilityBase> AbilityClass;

	// Gameplay tag that identifies this ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FGameplayTag AbilityTag;
	// Gameplay tags that will block this ability from being activated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FGameplayTagContainer AbilityBlockTags;
	// Test only
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float StaminaCost;
	
};
