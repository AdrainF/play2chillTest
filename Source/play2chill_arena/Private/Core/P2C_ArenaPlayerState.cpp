// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/P2C_ArenaPlayerState.h"

#include "Core/P2C_ArenaGameState.h"
#include "Net/UnrealNetwork.h"

void AP2C_ArenaPlayerState::OnRep_KillCount() const
{
	OnKillCountChanged.Broadcast(KillCount);
}

void AP2C_ArenaPlayerState::OnRep_WantsRestart() const
{
	if (AP2C_ArenaGameState* GS = GetWorld()->GetGameState<AP2C_ArenaGameState>())
	{
		GS->OnRestartUpdated.Broadcast();
	}
}

void AP2C_ArenaPlayerState::AddKill()
{
	if (HasAuthority())
	{
		KillCount++;
		OnRep_KillCount();
	}
}

void AP2C_ArenaPlayerState::SetWantsRestart_Implementation(bool WantsRestart)
{
	bWantsRestart = WantsRestart;
	OnRep_WantsRestart();
}


void AP2C_ArenaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AP2C_ArenaPlayerState, KillCount);
}
