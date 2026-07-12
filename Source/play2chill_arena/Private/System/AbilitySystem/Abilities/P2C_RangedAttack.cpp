// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/Abilities/P2C_RangedAttack.h"

#include "Camera/CameraComponent.h"
#include "Characters/P2C_PlayerCharacter.h"
#include "Items/Weapons/P2C_WeaponBase.h"

void UP2C_RangedAttack::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	
	if (ensureAlways(ClassToSpawn))
	{
		AP2C_PlayerCharacter* Character= GetP2CCharacter();
		if (!Character->HasAuthority()) return; 
		if (!Character || !Character->EquippedWeapon || !Character->EquippedWeapon->WeaponMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnProjectile: Missing weapon mesh on client/server! Aborting."));
			return;
		}
		FVector HandLocation = Character->EquippedWeapon->WeaponMesh->GetSocketLocation(SpawnSocketName);

		FHitResult Hit;
		FVector TraceStart;
		FVector TraceEnd;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FVector LookDir =Character->GetControlRotation().Vector();
		FVector CameraLoc =Character->FollowCamera->GetComponentLocation();
		TraceStart = CameraLoc+(LookDir+30.0f);
		TraceEnd = CameraLoc + (LookDir * 5000);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Character);
		Params.AddIgnoredActor(Character->EquippedWeapon);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Character;
		

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FRotator ProjRotation;

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		}
	
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);


	}
}

void UP2C_RangedAttack::PerformRangedAttack()
{
	AP2C_PlayerCharacter* P2CCharacter = GetP2CCharacter();

	if (P2CCharacter && MontageToPlay)
	{
		P2CCharacter->Server_PlayAttack(MontageToPlay);
		
		float Duration = P2CCharacter->PlayAnimMontage(MontageToPlay);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = P2CCharacter->GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &UP2C_RangedAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);
				
				FOnMontageBlendingOutStarted BlendDelegate;
				BlendDelegate.BindUObject(this, &UP2C_RangedAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendDelegate, MontageToPlay);

				P2CCharacter->GetWorldTimerManager().SetTimer(AttackTimer,this, &UP2C_RangedAttack::PrimayAtttack_TimeElapsed,  DelayTime);
			}
		}
		else
		{
			FinishAbility();
		}
	}
	
}

void UP2C_RangedAttack::Internal_StartAbility(UP2C_AbilitySystemComponent* InComp, const UP2C_AbilityDataAsset* InDA)
{
	Super::Internal_StartAbility(InComp, InDA);

	PerformRangedAttack();
}

void UP2C_RangedAttack::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	FinishAbility();
}

void UP2C_RangedAttack::PrimayAtttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}
