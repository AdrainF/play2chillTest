// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Consumable/P2C_ConsumableBase.h"

#include "Components/SphereComponent.h"

AP2C_ConsumableBase::AP2C_ConsumableBase()
{
	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CollisionComp);
}
