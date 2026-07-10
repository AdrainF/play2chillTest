// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Data/P2C_ItemDataAssetBase.h"
#include "P2C_ConsumableDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_ConsumableDataAsset : public UP2C_ItemDataAssetBase
{
	GENERATED_BODY()

public:
	virtual void ExecutePickupEffect(AActor* Interactor) const override; 
};
