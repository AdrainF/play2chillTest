// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "P2C_ArenaPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountChanged, int32, NewKillCount);

UCLASS()
class PLAY2CHILL_ARENA_API AP2C_ArenaPlayerState : public APlayerState
{
	GENERATED_BODY()

public:	
	UPROPERTY(ReplicatedUsing = OnRep_KillCount, BlueprintReadOnly, Category = "Stats")
	int32 KillCount = 0;
 
	UFUNCTION()
	void OnRep_KillCount() const;

	UPROPERTY(ReplicatedUsing = OnRep_WantsRestart, BlueprintReadOnly)
	bool bWantsRestart = false;
 
	UFUNCTION()
	void OnRep_WantsRestart() const;
	
	void AddKill();
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Arena")
	void SetWantsRestart(bool WantsRestart);
 
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKillCountChanged OnKillCountChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnKillCountChanged OnWantsRestartChanged;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
