// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2C_LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_LobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void AttemptStartGame();

protected:
	bool CheckAllPlayersReady() const;
};
