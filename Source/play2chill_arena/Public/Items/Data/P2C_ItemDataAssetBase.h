// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "P2C_ItemDataAssetBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_ItemDataAssetBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ItemMesh;

	/** This function is called when the item is picked up by an player.
	* @param Interactor - The actor that picked up the item.
	*/
	virtual void ExecutePickupEffect(AActor* Interactor) const
		PURE_VIRTUAL(UP2C_ItemDataAssetBase::ExecutePickupEffect, );
	
};
