// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_PlayerController.h"

#include "Components/P2C_AttributionComponent.h"
#include "UI/P2C_PlayerWidget.h"

void AP2C_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && HUDClass)
	{
		PlayerHUD = CreateWidget<UP2C_PlayerWidget>(this, HUDClass);
		PlayerHUD->AddToViewport();
        
		UP2C_AttributionComponent* AttriComp= Cast<UP2C_AttributionComponent>(
			GetPawn()->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));
		if (AttriComp)
		{
			AttriComp->OnHealthChanged.AddDynamic(PlayerHUD.Get(), &UP2C_PlayerWidget::UpdateHealth);
			AttriComp->OnStaminaChanged.AddDynamic(PlayerHUD, &UP2C_PlayerWidget::UpdateStamina);
			AttriComp->OnKillCountChanged.AddDynamic(PlayerHUD, &UP2C_PlayerWidget::UpdateKillCount);

			PlayerHUD->UpdateHealth(
						AttriComp, 
						AttriComp->GetHealth(), 
						AttriComp->GetHealth(), 
						AttriComp->GetMaxHealth(), 
						nullptr, nullptr
					);
 
			PlayerHUD->UpdateStamina(
				AttriComp,
				AttriComp->GetStamina(),
				AttriComp->GetStamina(),
				AttriComp->GetMaxStamina()
			);
 
			PlayerHUD->UpdateKillCount(AttriComp->GetKillCount());
		
		}
	}
}
