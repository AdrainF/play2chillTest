// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/P2C_PickupItem.h"

#include "Components/SphereComponent.h"
#include "Items/Data/P2C_ItemDataAssetBase.h"


void AP2C_PickupItem::Interact_Implementation(AActor* Interactor)
{
	if (HasAuthority())
	{
		if (ItemDataAsset)
		{
			ItemDataAsset->ExecutePickupEffect(Interactor);
			Destroy();
		}
	}
}

// Sets default values
AP2C_PickupItem::AP2C_PickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true; 

	CollisionComp=CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent=CollisionComp;

}

// Called when the game starts or when spawned
void AP2C_PickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP2C_PickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

