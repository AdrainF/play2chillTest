// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/P2C_PickupItem.h"
#include "P2C_ConsumableBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_ConsumableBase : public AP2C_PickupItem
{
	GENERATED_BODY()

public:
	AP2C_ConsumableBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* MeshComponent;
};
