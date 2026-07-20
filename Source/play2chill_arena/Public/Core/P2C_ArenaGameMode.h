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
	void NotifyKill(AController* Killer, AController* Victim);
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	void RequestRespawn(AController* Controller);
protected:

	void RespawnPlayer(TWeakObjectPtr<AController> ControllerPtr);
 
	UPROPERTY(EditAnywhere, Category = "Rules")
	float RespawnDelay = 3.0f;

	void CheckAllPlayersRestart();
	
	void RestartArenaLevel();
	void EndMatchWithWinner(AP2C_ArenaPlayerState* Winner);
	UPROPERTY()
	TArray<AActor*> AvailableStarts;

	void Tick(float DeltaSeconds) override;
};
