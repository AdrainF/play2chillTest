// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/P2C_PickupItem.h"
#include "P2C_WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API AP2C_WeaponBase : public AP2C_PickupItem
{
	GENERATED_BODY()

public:
	AP2C_WeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USkeletalMeshComponent* WeaponMesh;


	UFUNCTION(BlueprintCallable, Category = "WeaponCollison")
	void StartTrace();
	UFUNCTION(BlueprintCallable, Category = "WeaponCollison")
	void EndTrace();
	UFUNCTION(BlueprintCallable, Category = "WeaponCollison")
	void DoFrameToFrameTrace();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName SocketBaseName = "Socket_Base";
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName SocketTipName = "Socket_Tip";
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ProjectileRadius = 30.0f;
	bool bIsTracing = false;
	
	uint64 LastStartFrame = 0;
	uint64 LastEndFrame = 0;
	
	UPROPERTY()
	TSet<AActor*> HitActors;
	virtual void Tick(float DeltaTime) override;
};
