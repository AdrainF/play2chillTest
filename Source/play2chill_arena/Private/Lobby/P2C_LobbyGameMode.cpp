// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/P2C_LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "Lobby/P2C_LobbyPlayerState.h"

void AP2C_LobbyGameMode::AttemptStartGame()
{
	if (CheckAllPlayersReady())
	{
		// "listen" option allows clients to follow the server to the new map
		GetWorld()->ServerTravel(TEXT("/Game/Levels/ArenaMap?listen"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not all players are ready!"));
	}
}

bool AP2C_LobbyGameMode::CheckAllPlayersReady() const
{
	if (!GameState) return false;
 
	// Iterate through all PlayerStates in the GameState
	for (APlayerState* PS : GameState->PlayerArray)
	{
		AP2C_LobbyPlayerState* LobbyPS = Cast<AP2C_LobbyPlayerState>(PS);
		if (LobbyPS)
		{
			if (!LobbyPS->bIsReady)
			{
				return false; // Found someone not ready
			}
		}
	}
 
	return true;
}
