// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/P2C_WeaponBase.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_AttributionComponent.h"
#include "Components/SphereComponent.h"
#include "Items/Data/MyP2C_WeaponDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"


AP2C_WeaponBase::AP2C_WeaponBase()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick= true;
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(CollisionComp);

	bReplicates = true;
	SetNetCullDistanceSquared(FMath::Square(5000.0f));
}

void AP2C_WeaponBase::ClearHitActors_Implementation()
{
	HitActors.Empty();
}

bool AP2C_WeaponBase::ClearHitActors_Validate()
{
	return true;
}

void AP2C_WeaponBase::Request_ClearHitActors()
{
	if (!GetOwner()->HasAuthority())
	{
		ClearHitActors();
	}
	else
	{
		HitActors.Empty();
	}
}

void AP2C_WeaponBase::SetTraceWeapon(bool isTracing)
{
	bTraceWeapon=isTracing;
	if (isTracing)
	{
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorTickEnabled(false);
	}
}

void AP2C_WeaponBase::WeaponTrace()
{
	
		if (!Owner  || !Owner->HasAuthority()) { return; }
		AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(Owner);
	
		if (!Char || !Char->EquippedWeapon) { return; };
	
		if (AP2C_WeaponBase* Weapon = Char->EquippedWeapon)
		{
			FVector CurrentBase = Weapon->WeaponMesh->GetSocketLocation(Weapon->SocketBaseName);
			FVector CurrentTip = Weapon->WeaponMesh->GetSocketLocation(Weapon->SocketTipName);
	
			TArray<FHitResult> OutHits;
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(Weapon);
			ActorsToIgnore.Add(Char);
	
	
			float WeaponRadius = 30;
	
			bool bHit = UKismetSystemLibrary::SphereTraceMulti(
				GetWorld(),
				CurrentBase, CurrentTip,
				WeaponRadius,
				UEngineTypes::ConvertToTraceType(ECC_Pawn),
				false,
				ActorsToIgnore,
				EDrawDebugTrace::ForDuration,
				OutHits,
				true,
				FLinearColor::Red,      // TraceColor
				FLinearColor::Green,    // TraceHitColor
			2.0f   
			);
	
			if (bHit)
			{
				for (const FHitResult& Hit : OutHits)
				{
					AP2C_PlayerCharacter* Victim = Cast<AP2C_PlayerCharacter>(Hit.GetActor());
					if (Victim && !Weapon->HitActors.Contains(Victim))
					{
						if (UP2C_AttributionComponent* AttriComp = Victim->GetComponentByClass<
							UP2C_AttributionComponent>())
						{
							UMyP2C_WeaponDataAsset*	WeaponDA = Cast<UMyP2C_WeaponDataAsset>(Char->EquippedWeapon->ItemDataAsset);
							float Damage = WeaponDA->Damage;
							Weapon->HitActors.Add(Victim);
							Victim->AttrComp->Server_ApplyHealthChange(Damage, Char, Victim);
							UE_LOG(LogTemp, Warning, TEXT("UniqueHitActor name: %s"), *Victim->GetName());
						}
						UE_LOG(LogTemp, Warning, TEXT("Sweep Hit: %s"), *Victim->GetName());
					}
				}
			}
		}
}

void AP2C_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bTraceWeapon)
	{
		WeaponTrace();
	}
}
