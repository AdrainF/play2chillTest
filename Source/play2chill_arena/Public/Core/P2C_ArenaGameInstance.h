// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "P2C_ArenaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_ArenaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UP2C_ArenaGameInstance();

	// Creat e a LAN match with the specified maximum number of players
	UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
	void HostLANMatch(int32 MaxPlayers = 4);
 
	// Find and join a LAN match
	UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
	void FindAndJoinLANMatch();
 
protected:
	virtual void Init() override;
 
	// Callbacks for session events
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
 
private:
	// The name of the session we are creating/joining
	const FName MySessionName = NAME_GameSession;
 
	IOnlineSessionPtr  SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	// Flag to indicate if we are restarting the session after destroying it
	bool bIsRestartingSession = false;
	int32 PendingMaxPlayers = 4;

	FDelegateHandle DestroySessionAndJoinHandle;
	// Internal function to create a LAN session
	void CreateLANSessionInternal(int32 MaxPlayers);
	
};
