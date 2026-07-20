// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "P2C_LobbyGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLobbyUpdated);

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_LobbyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Lobby")
	FOnLobbyUpdated OnLobbyUpdated;
	
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void GetLobbyCounts(int32& OutReadyCount, int32& OutTotalCount);
	
	virtual void AddPlayerState(APlayerState* PlayerState) override;
    virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
