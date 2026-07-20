// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"
#include "P2C_RangedAttack.generated.h"

/**
* Ability class that handles montage playback and projectile spawning for ranged combat.
*/
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_RangedAttack : public UP2C_AbilityBase
{
	GENERATED_BODY()

	public:
	/** Projectile asset and spawn location data. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName SpawnSocketName;
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float DelayTime;
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	/** Calculates aiming trajectory and requests projectile spawning via the network component. */
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	/** Initiates the attack montage and sets up lifecycle delegates. */
	UFUNCTION(BlueprintCallable, Category = "Ranged Attack Combo")
	void PerformRangedAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Attack Combo")
	TObjectPtr<UAnimMontage> MontageToPlay;

	virtual void Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA) override;
	
protected:
	/** Cleans up the ability state once the animation finishes or blends out. */
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	/** Cleans up the ability state once the animation finishes or blends out. */
	UFUNCTION()
	void PrimaryAttack_TimeElapsed();
};
