// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/P2C_WeaponBase.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_AttributionComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AP2C_WeaponBase::AP2C_WeaponBase()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	
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

void AP2C_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
