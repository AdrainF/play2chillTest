// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/P2C_LobbyPlayerState.h"

#include "Lobby/P2C_LobbyGameState.h"
#include "Net/UnrealNetwork.h"

AP2C_LobbyPlayerState::AP2C_LobbyPlayerState()
{
	bIsReady = false;
}

void AP2C_LobbyPlayerState::OnRep_IsReady()
{
	if (AP2C_LobbyGameState* GS = GetWorld()->GetGameState<AP2C_LobbyGameState>())
	{
		GS->OnLobbyUpdated.Broadcast();
	}
}

void AP2C_LobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AP2C_LobbyPlayerState, bIsReady);
}

void AP2C_LobbyPlayerState::Server_SetReady_Implementation(bool bNewReady)
{
	bIsReady = bNewReady;
	if (AP2C_LobbyGameState* GS = GetWorld()->GetGameState<AP2C_LobbyGameState>())
	{
		GS->OnLobbyUpdated.Broadcast();
	}
}
