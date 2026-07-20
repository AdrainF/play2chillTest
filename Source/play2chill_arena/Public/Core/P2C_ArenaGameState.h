// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "P2C_ArenaGameState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartUpdated);

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_ArenaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Restart")
	FOnRestartUpdated OnRestartUpdated;

	UFUNCTION(BlueprintCallable, Category = "Restart")
	void GetRestartCounts(int32& OutRestartCount, int32& OutTotalCount);
 
	
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
