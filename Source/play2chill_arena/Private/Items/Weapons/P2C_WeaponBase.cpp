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

void AP2C_WeaponBase::StartTrace()
{
	if (!HasAuthority()) return;
	bIsTracing = true;
	if (GFrameCounter == LastStartFrame) return;
	LastStartFrame = GFrameCounter;
	
	HitActors.Empty();
	SetActorTickEnabled(true);
	
	WeaponMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	if (AP2C_PlayerCharacter* OwnerChar = Cast<AP2C_PlayerCharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* CharMesh = OwnerChar->GetMesh())
		{
			CharMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
		}
	}
}

void AP2C_WeaponBase::EndTrace()
{
	if (!HasAuthority()) return;
	SetActorTickEnabled(false);
	bIsTracing=false;
	if (GFrameCounter == LastStartFrame) return;
	LastStartFrame = GFrameCounter;
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
				
				if (UP2C_AttributionComponent* AttriComp = Victim->GetComponentByClass<UP2C_AttributionComponent>())
				{
					HitActors.Add(Victim);
					AttriComp->Server_ApplyHealthChange(-10, GetOwner(), Victim);
					UE_LOG(LogTemp, Warning, TEXT("UniqueHitActor name: %s"), *Victim->GetName());
				}
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
