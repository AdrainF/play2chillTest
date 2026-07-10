// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Data/P2C_ConsumableDataAsset.h"

#include "Components/P2C_AttributionComponent.h"

void UP2C_ConsumableDataAsset::ExecutePickupEffect(AActor* Interactor) const
{
	if (!Interactor) return;
	
	UP2C_AttributionComponent* AttiComp= Interactor->GetComponentByClass<UP2C_AttributionComponent>();

	if (AttiComp)
	{
		AttiComp->Server_ApplyHealthChange(20.0f,Interactor,nullptr);
	}
}
