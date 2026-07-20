// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/P2C_ArenaGameState.h"

#include "Core/P2C_ArenaPlayerState.h"

void AP2C_ArenaGameState::GetRestartCounts(int32& OutRestartCount, int32& OutTotalCount)
{
	// Aggregates player restart statuses for UI display.
	OutRestartCount = 0;
	OutTotalCount = PlayerArray.Num();
 
	for (APlayerState* PS : PlayerArray)
	{
		if (AP2C_ArenaPlayerState* ArenaPS = Cast<AP2C_ArenaPlayerState>(PS))
		{
			if (ArenaPS->bWantsRestart) OutRestartCount++;
		}
	}
}

void AP2C_ArenaGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	// Ensures UI updates when a new player joins.
	OnRestartUpdated.Broadcast();
}

void AP2C_ArenaGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
	// Ensures UI updates when a player leaves.
	OnRestartUpdated.Broadcast();
}
