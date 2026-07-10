// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Data/P2C_ItemDataAssetBase.h"
#include "MyP2C_WeaponDataAsset.generated.h"

/**
 * 
 */
class UP2C_AbilityDataAsset;
class USkeletalMesh;

UCLASS()
class PLAY2CHILL_ARENA_API UMyP2C_WeaponDataAsset : public UP2C_ItemDataAssetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TObjectPtr<UP2C_AbilityDataAsset> WeaponAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float AttackCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AActor> WeaponActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TObjectPtr<USkeletalMesh> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Socket")
	FName WeaponSocket;
	
	virtual void ExecutePickupEffect(AActor* Interactor) const override; 
};
