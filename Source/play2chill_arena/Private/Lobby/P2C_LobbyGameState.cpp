// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/P2C_LobbyGameState.h"

#include "GameFramework/PlayerState.h"
#include "Lobby/P2C_LobbyPlayerState.h"

class AP2C_LobbyPlayerState;

void AP2C_LobbyGameState::GetLobbyCounts(int32& OutReadyCount, int32& OutTotalCount)
{
	OutReadyCount = 0;
	OutTotalCount = PlayerArray.Num();
 
	for (APlayerState* PS : PlayerArray)
	{
		if (AP2C_LobbyPlayerState* LobbyPS = Cast<AP2C_LobbyPlayerState>(PS))
		{
			if (LobbyPS->bIsReady) OutReadyCount++;
		}
	}
}

void AP2C_LobbyGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	OnLobbyUpdated.Broadcast();
}

void AP2C_LobbyGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
	OnLobbyUpdated.Broadcast();
}
