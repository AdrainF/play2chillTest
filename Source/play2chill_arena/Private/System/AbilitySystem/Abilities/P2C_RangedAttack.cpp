// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AbilitySystem/Abilities/P2C_RangedAttack.h"

#include "Camera/CameraComponent.h"
#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_NetworkComponent.h"
#include "Items/Weapons/P2C_WeaponBase.h"

void UP2C_RangedAttack::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	
	if (ensureAlways(ClassToSpawn))
	{
		AP2C_PlayerCharacter* Character= GetP2CCharacter();

		if (!Character || !Character->EquippedWeapon )
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnProjectile: Missing weapon on client/server!"));
			return;
		}
		// The projectile spawns at the weapon muzzle but aims at what the camera is looking 
		FVector WeaponLocation = Character->EquippedWeapon->WeaponMesh->GetSocketLocation(SpawnSocketName);
		// Trace from camera to find the world impact point for accurate aiming.
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
			// Adjust rotation to point from the muzzle to the actual crosshair impact point.
			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - WeaponLocation).Rotator();
		}
		else
		{
			// Fallback to aiming towards the end of the trace range.
			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - WeaponLocation).Rotator();
		}
		
		FTransform SpawnTM = FTransform(ProjRotation, WeaponLocation);
		// Delegate the actual spawning to the network component for server authority.
		Character->NetworkComp->Request_SpawnProjectile(ClassToSpawn, WeaponLocation, ProjRotation);
		
	}
}


void UP2C_RangedAttack::PerformRangedAttack()
{
	AP2C_PlayerCharacter* P2CCharacter = GetP2CCharacter();

	if (P2CCharacter && MontageToPlay)
	{	// Sync animation playback across the network.
		P2CCharacter->NetworkComp->Server_PlayAttack(MontageToPlay);
		
		float Duration = P2CCharacter->PlayAnimMontage(MontageToPlay);
		if (Duration > 0.0f)
		{
			UAnimInstance* AnimInstance = P2CCharacter->GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				// Bind delegates to ensure the ability finishes correctly.
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &UP2C_RangedAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);
				
				FOnMontageBlendingOutStarted BlendDelegate;
				BlendDelegate.BindUObject(this, &UP2C_RangedAttack::OnAttackMontageEnded);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendDelegate, MontageToPlay);

				// Start the timer for the delayed projectile launch.
				P2CCharacter->GetWorldTimerManager().SetTimer(AttackTimer,this, &UP2C_RangedAttack::PrimaryAttack_TimeElapsed,  DelayTime);
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

void UP2C_RangedAttack::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}
