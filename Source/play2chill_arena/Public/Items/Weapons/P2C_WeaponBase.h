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

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName SocketBaseName = "Socket_Base";
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName SocketTipName = "Socket_Tip";
	UPROPERTY(EditAnywhere, Category = "Combat")
	float TraceRadius = 30.0f;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Request_ClearHitActors();
	UFUNCTION(Server, Reliable, WithValidation)
	void ClearHitActors();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetTraceWeapon(bool isTracing);
	
	UFUNCTION()
	void WeaponTrace();
	UPROPERTY()
	TSet<AActor*> HitActors;
	protected:
	UPROPERTY()
	bool bTraceWeapon=false;
	virtual void Tick(float DeltaTime) override;
};
