// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/P2C_PlayerController.h"

#include "Components/P2C_AttributionComponent.h"
#include "UI/P2C_PlayerWidget.h"


void AP2C_PlayerController::Client_SetGameInputMode_Implementation()
{
	bShowMouseCursor = false;


	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
}


void AP2C_PlayerController::Client_ShowEndRoundWidget_Implementation()
{
	if (RestartWidgetClass)
	{
		UUserWidget* RestartWidget = CreateWidget<UUserWidget>(this, RestartWidgetClass);
		if (RestartWidget)
		{
			RestartWidget->AddToViewport();
			
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
		}
	}
}

void AP2C_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Client_SetGameInputMode();
}

void AP2C_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	
}

void AP2C_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (IsLocalController() && HUDClass)
	{
		PlayerHUD = CreateWidget<UP2C_PlayerWidget>(this, HUDClass);
		PlayerHUD->AddToViewport();
		
		if (IsValid(P))
		{
			UP2C_AttributionComponent* AttriComp = Cast<UP2C_AttributionComponent>(
				P->GetComponentByClass(UP2C_AttributionComponent::StaticClass()));

			if (AttriComp)
			{
				if (!AttriComp->OnHealthChanged.IsAlreadyBound(PlayerHUD, &UP2C_PlayerWidget::UpdateHealth))
				{
					AttriComp->OnHealthChanged.AddDynamic(PlayerHUD, &UP2C_PlayerWidget::UpdateHealth);
				}
				AttriComp->OnStaminaChanged.AddDynamic(PlayerHUD, &UP2C_PlayerWidget::UpdateStamina);
				
				
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
				
			}
		}
	}
}
