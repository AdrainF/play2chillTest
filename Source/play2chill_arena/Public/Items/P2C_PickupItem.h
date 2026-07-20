// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/P2C_InteractionInterface.h"
#include "P2C_PickupItem.generated.h"

class USphereComponent;
class UP2C_ItemDataAssetBase;

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_PickupItem : public AActor, public IP2C_InteractionInterface
{
	GENERATED_BODY()

	void Interact_Implementation(AActor* Interactor) ;
	
public:	
	// Sets default values for this actor's properties
	AP2C_PickupItem();
	
	// The data asset that defines the properties and behavior of this pickup item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UP2C_ItemDataAssetBase* ItemDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<USphereComponent> CollisionComp;
	
};
