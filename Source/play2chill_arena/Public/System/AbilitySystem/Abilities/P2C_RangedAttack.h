// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"
#include "P2C_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_RangedAttack : public UP2C_AbilityBase
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName SpawnSocketName;
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float DelayTime;
	
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	UFUNCTION(BlueprintCallable, Category = "Ranged Attack Combo")
	void PerformRangedAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Attack Combo")
	TObjectPtr<UAnimMontage> MontageToPlay;

	virtual void Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA) override;
	
protected:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void PrimayAtttack_TimeElapsed();
};
