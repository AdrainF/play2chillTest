// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P2C_PlayerWidget.generated.h"
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_PlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Add functions to update the player's health, stamina, and kill count
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(UP2C_AttributionComponent* AttributionComponent, float Health, float MaxValue, float Delta, AActor* InstigatorActor, AActor* DamagedActor);
	UFUNCTION(BlueprintCallable)
	void UpdateStamina(UP2C_AttributionComponent* AttributionComponent, float OldValue, float NewValue, float MaxValue);
	UFUNCTION(BlueprintCallable)
	void UpdateKillCount( const int32 NewKillCount);

protected:
	// Bind the health bar, stamina bar, and kill count text to the widget
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> KillCountText;
};
