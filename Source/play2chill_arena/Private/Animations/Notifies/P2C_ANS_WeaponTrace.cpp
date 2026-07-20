// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/P2C_ANS_WeaponTrace.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_AttributionComponent.h"
#include "Items/Data/MyP2C_WeaponDataAsset.h"
#include "Items/Weapons/P2C_WeaponBase.h"
#include "Kismet/KismetSystemLibrary.h"


void UP2C_ANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner  || !Owner->HasAuthority()) { return; }
		
		if (AP2C_PlayerCharacter* Char = Cast<AP2C_PlayerCharacter>(MeshComp->GetOwner()))
		{
			if (Char->EquippedWeapon)
			{
				UMyP2C_WeaponDataAsset*	WeaponDA = Cast<UMyP2C_WeaponDataAsset>(Char->EquippedWeapon->ItemDataAsset);
				Damage = WeaponDA->Damage;
				UE_LOG(LogTemp, Error, TEXT("!!! NOTIFY BEGIN !!! Cleaning Weapon: %s (Address: %p)"), 
				*Char->EquippedWeapon->GetName(), Char->EquippedWeapon.Get());
			}
		}
	
}

void UP2C_ANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{

}



void UP2C_ANS_WeaponTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	UWorld* World = MeshComp ? MeshComp->GetWorld() : nullptr;
	
	
	if (!World) return;

	AActor* Owner = MeshComp->GetOwner();
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
			World,
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
