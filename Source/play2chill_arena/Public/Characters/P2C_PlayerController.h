// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P2C_PlayerController.generated.h"

class UP2C_PlayerWidget;
/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// The class of the HUD widget to create and display
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDClass;

protected:
	virtual void BeginPlay() override;

private:
	// Reference to the player's HUD widget
	UPROPERTY()
	TObjectPtr<UP2C_PlayerWidget> PlayerHUD;
};
