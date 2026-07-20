// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/P2C_ArenaGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"



UP2C_ArenaGameInstance::UP2C_ArenaGameInstance()
{
}

void UP2C_ArenaGameInstance::HostLANMatch(int32 MaxPlayers)
{
	if (!SessionInterface.IsValid()) return;
 
	PendingMaxPlayers = MaxPlayers;
 
	// Check if a session with the same name already exists. If it does, destroy it first.
	if (SessionInterface->GetNamedSession(MySessionName))
	{
		bIsRestartingSession = true;
		SessionInterface->DestroySession(MySessionName);
	}
	else
	{
		CreateLANSessionInternal(MaxPlayers);
	}
}

void UP2C_ArenaGameInstance::FindAndJoinLANMatch()
{
	if (!SessionInterface.IsValid()) return;
 
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 10;
	
	SessionSearch->QuerySettings.Set(FName(TEXT("PRESENCESEARCH")), true, EOnlineComparisonOp::Equals);
 
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UP2C_ArenaGameInstance::Init()
{
	
	Super::Init();
 
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UP2C_ArenaGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UP2C_ArenaGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UP2C_ArenaGameInstance::OnJoinSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UP2C_ArenaGameInstance::OnDestroySessionComplete);
		}
	}
}

void UP2C_ArenaGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("LAN Session Created. Hosting..."));
		
		UGameplayStatics::OpenLevel(GetWorld(), "LobbyMap", true, "listen");
	}
}


void UP2C_ArenaGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!SessionInterface.IsValid() || !bWasSuccessful || !SessionSearch.IsValid()) return;
 
	if (SessionSearch->SearchResults.Num() > 0)
	{
		//Check if we already have a session with the same name. If we do, we need to destroy it before joining the new one.
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(MySessionName);
		if (ExistingSession)
		{
			// If we are the host, we should not try to join our own session. Just ignore it.
			if (GetWorld()->GetNetMode() == NM_ListenServer)
			{
				UE_LOG(LogTemp, Warning, TEXT("Host: Found my own session. Ignoring."));
				return;
			}
			
			UE_LOG(LogTemp, Log, TEXT("Client: Destroying old session state before joining..."));
            
			//Remove the previous delegate to avoid multiple calls
			SessionInterface->OnDestroySessionCompleteDelegates.Remove(DestroySessionAndJoinHandle);
 
			DestroySessionAndJoinHandle = SessionInterface->OnDestroySessionCompleteDelegates.AddLambda([this](FName SessionName, bool bDestroySuccess)
			{
				SessionInterface->OnDestroySessionCompleteDelegates.Remove(DestroySessionAndJoinHandle);
                
				if (bDestroySuccess && SessionSearch->SearchResults.Num() > 0)
				{
					SessionInterface->JoinSession(0, MySessionName, SessionSearch->SearchResults[0]);
				}
			});
 
			SessionInterface->DestroySession(MySessionName);
			return;
		}
		
		SessionInterface->JoinSession(0, MySessionName, SessionSearch->SearchResults[0]);
	}
}

void UP2C_ArenaGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		if (APlayerController* PC = GetFirstLocalPlayerController())
		{
			FString ConnectString;
			if (SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
			{
				PC->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UP2C_ArenaGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessfu)
{
	if (bIsRestartingSession)
	{
		bIsRestartingSession = false;
		CreateLANSessionInternal(PendingMaxPlayers);
	}
}

void UP2C_ArenaGameInstance::CreateLANSessionInternal(int32 MaxPlayers)
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = MaxPlayers;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bAllowJoinInProgress = true;

	SessionSettings.Set(FName(TEXT("MAPNAME")), FString("LobbyMap"), EOnlineDataAdvertisementType::ViaOnlineService);
	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}
