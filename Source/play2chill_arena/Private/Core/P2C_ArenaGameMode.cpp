// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/P2C_ArenaGameMode.h"

#include "Characters/P2C_PlayerController.h"
#include "Core/P2C_ArenaPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AActor* AP2C_ArenaGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (AvailableStarts.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AvailableStarts);
	}

	if (GameState)
	{
		int32 PlayerIndex = GameState->PlayerArray.Find(Player->PlayerState);
        
		
		if (AvailableStarts.IsValidIndex(PlayerIndex))
		{
			return AvailableStarts[PlayerIndex];
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

void AP2C_ArenaGameMode::RequestRespawn(AController* Controller)
{
	if (!Controller || !IsValid(Controller)) return;
 
		// Unpossess the pawn if it still exists
		Controller->UnPossess();
 
		// Set a timer for the respawn
		FTimerHandle RespawnTimerHandle;
		FTimerDelegate RespawnDelegate;

		TWeakObjectPtr<AController> SafeControllerPtr(Controller);
		// Use a delegate to pass the Controller parameter to the timer
		RespawnDelegate.BindUObject(this, &AP2C_ArenaGameMode::RespawnPlayer, SafeControllerPtr);
 
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
	
}

void AP2C_ArenaGameMode::RespawnPlayer(TWeakObjectPtr<AController> ControllerPtr)
{
	AController* Controller = ControllerPtr.Get();
	if (Controller)
	{
		
		RestartPlayer(Controller);
        
		UE_LOG(LogTemp, Log, TEXT("Player %s respowned."), *Controller->GetName());
	}
}

AP2C_ArenaGameMode::AP2C_ArenaGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PrimaryActorTick.TickInterval = 0.1f;
	
}

void AP2C_ArenaGameMode::NotifyKill(AController* Killer, AController* Victim)
{
	if (!Killer || !Victim) return;
 
	AP2C_ArenaPlayerState* KillerState = Killer->GetPlayerState<AP2C_ArenaPlayerState>();
	if (KillerState)
	{
		KillerState->AddKill();
 
		
		if (KillerState->KillCount >= 2)
		{
			EndMatchWithWinner(KillerState);
		}
	}
}

void  AP2C_ArenaGameMode::CheckAllPlayersRestart()
{
	if (!GameState) return;
 
	// Iterate through all PlayerStates in the GameState
	for (APlayerState* PS : GameState->PlayerArray)
	{
		AP2C_ArenaPlayerState* ArenaPS = Cast<AP2C_ArenaPlayerState>(PS);
		if (ArenaPS)
		{
			if (!ArenaPS->bWantsRestart)
			{
				return; // Found someone not ready
			}
			
		}
	}
 
	RestartArenaLevel();
}

void AP2C_ArenaGameMode::RestartArenaLevel()
{
	SetActorTickEnabled(false);
    
	bUseSeamlessTravel = true;
	GetWorld()->ServerTravel(TEXT("/Game/Levels/ArenaMap?listen"));
}

void AP2C_ArenaGameMode::EndMatchWithWinner(AP2C_ArenaPlayerState* Winner)
{
	SetActorTickEnabled(true);
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC)
		{
			AP2C_PlayerController* MyPCC= Cast<AP2C_PlayerController>(PC);
			if (MyPCC)
			{
				MyPCC->Client_ShowEndRoundWidget();
			}
		}
	}
}

void AP2C_ArenaGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckAllPlayersRestart();
}
