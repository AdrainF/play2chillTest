// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P2C_PlayerWidget.h"

#include "Components/P2C_AttributionComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UP2C_PlayerWidget::UpdateHealth(UP2C_AttributionComponent* AttributionComponent, float Health, float  MaxValue , float Delta , AActor* InstigatorActor, AActor* DamagedActor)
{
		HealthBar->SetPercent(Health / MaxValue);
}

void UP2C_PlayerWidget::UpdateStamina(UP2C_AttributionComponent* AttributionComponent, float Stamina, float MaxValue, float DeltaValue)
{
		StaminaBar->SetPercent(Stamina / MaxValue);
}
