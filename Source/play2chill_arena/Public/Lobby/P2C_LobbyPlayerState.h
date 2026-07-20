// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "P2C_LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_LobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AP2C_LobbyPlayerState();
	
	// The replicated variable
	UPROPERTY(ReplicatedUsing = OnRep_IsReady, BlueprintReadOnly, Category = "Lobby")
	bool bIsReady;
 
	// Called when the variable replicates to clients
	UFUNCTION()
	void OnRep_IsReady();
 
	// RPC called by the client to update readiness on the server
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Lobby")
	void Server_SetReady(bool bNewReady);
 
	// Required for replication registration
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
