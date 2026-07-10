// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/P2C_PlayerWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UP2C_PlayerWidget::UpdateHealth(UP2C_AttributionComponent* AttributionComponent, float Health, float  MaxValue , float Delta , AActor* InstigatorActor, AActor* DamagedActor)
{
		HealthBar->SetPercent(Health / MaxValue);
}

void UP2C_PlayerWidget::UpdateStamina(UP2C_AttributionComponent* AttributionComponent, float OldValue, float MaxValue, float NewValue)
{
		StaminaBar->SetPercent(NewValue / MaxValue);
}

void UP2C_PlayerWidget::UpdateKillCount( const int32 NewKillCount)
{
		KillCountText->SetText(FText::AsNumber(NewKillCount));
}
