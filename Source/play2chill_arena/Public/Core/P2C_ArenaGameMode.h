// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2C_ArenaGameMode.generated.h"

/**
 * 
 */
class AP2C_ArenaPlayerState;
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_ArenaGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AP2C_ArenaGameMode();
	/** Notifies the game mode that a kill has occurred to update scores and check win conditions. */
	void NotifyKill(AController* Killer, AController* Victim);
	/** Overridden to determine the spawn point for a player. */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	/** Initiates the respawn process for a player controller after a delay. */
	void RequestRespawn(AController* Controller);
protected:

	void RespawnPlayer(TWeakObjectPtr<AController> ControllerPtr);
 
	UPROPERTY(EditAnywhere, Category = "Rules")
	float RespawnDelay = 3.0f;
	/** Number of kills required for a player to win the match. */
	UPROPERTY(EditDefaultsOnly, Category = "Rules")
	int KillsToWin = 5;
	/** Checks if all connected players have flagged themselves as ready to restart. */
	void CheckAllPlayersRestart();
	/** Performs a Server Travel to reload the arena level. */
	void RestartArenaLevel();
	/** Called when a player reaches the kill limit. Disables gameplay and shows UI. */
	void EndMatchWithWinner(AP2C_ArenaPlayerState* Winner);
	/** Cached list of player start actors found in the level. */
	UPROPERTY()
	TArray<AActor*> AvailableStarts;

	virtual void Tick(float DeltaSeconds) override;
};
