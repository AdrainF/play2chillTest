// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2C_LobbyGameMode.generated.h"

/**
* AP2C_LobbyGameMode
* Handles the pre-game lobby logic and transition to the gameplay map.
*/
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_LobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Validates lobby status and initiates the match if all conditions are met. */
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void AttemptStartGame();

protected:
	/** Returns true only if every connected player has toggled their ready status. */
	bool CheckAllPlayersReady() const;
};
