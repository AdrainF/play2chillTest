// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P2C_OverheadHealthWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_OverheadHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetHealthPercent(float Percent);
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
};
