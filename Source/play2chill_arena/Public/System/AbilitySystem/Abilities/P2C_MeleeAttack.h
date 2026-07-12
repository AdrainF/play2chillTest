// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/AbilitySystem/Abilities/P2C_AbilityBase.h"
#include "P2C_MeleeAttack.generated.h"

/**
 * 
 */
class UAnimMontage;
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_MeleeAttack : public UP2C_AbilityBase
{
	GENERATED_BODY()

public:
	UP2C_MeleeAttack();

	UFUNCTION(BlueprintCallable, Category = "Melee Attack Combo")
	void PerformMeleeAttack();

	virtual void Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Attack Combo")
	TObjectPtr<UAnimMontage> MontageToPlay;
protected:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
