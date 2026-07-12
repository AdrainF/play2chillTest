// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/P2C_WeaponBase.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AP2C_WeaponBase::AP2C_WeaponBase()
{
	
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(CollisionComp);

	bReplicates = true;
	SetNetCullDistanceSquared(FMath::Square(5000.0f));
}

void AP2C_WeaponBase::StartTrace()
{
	PrimaryActorTick.bCanEverTick=true;
	bIsTracing = true;
	HitActors.Empty();
	
}

void AP2C_WeaponBase::DoFrameToFrameTrace()
{
	if (!HasAuthority()) return;
 
	FVector CurrentBase = WeaponMesh->GetSocketLocation(SocketBaseName);
	FVector CurrentTip = WeaponMesh->GetSocketLocation(SocketTipName);
 
	TArray<FHitResult> OutHits;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
 
	
	float WeaponRadius = ProjectileRadius; 
	
	bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		CurrentBase, CurrentTip,
		WeaponRadius,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true
	);
 
	if (bHit)
	{
		for (const FHitResult& Hit : OutHits)
		{
			AActor* Victim = Hit.GetActor();
			if (Victim && !HitActors.Contains(Victim))
			{
				HitActors.Add(Victim);
				
				UE_LOG(LogTemp, Warning, TEXT("Sweep Hit: %s"), *Victim->GetName());
			}
		}
	}
	
}

void AP2C_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsTracing) { DoFrameToFrameTrace();}
}
