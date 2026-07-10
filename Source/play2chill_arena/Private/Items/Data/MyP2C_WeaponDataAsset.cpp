// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Data/MyP2C_WeaponDataAsset.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Items/Weapons/P2C_WeaponBase.h"
#include "System/AbilitySystem/P2C_AbilitySystemComponent.h"

void UMyP2C_WeaponDataAsset::ExecutePickupEffect(AActor* Interactor) const
{
	if (!Interactor || !WeaponActorClass) return;
	
	AP2C_PlayerCharacter* Character = Cast<AP2C_PlayerCharacter>(Interactor);
	if (!Character) return;
 
	UWorld* World = Interactor->GetWorld();
	if (!World) return;

	Character->AbilitySystemComp->GrantAbility(WeaponAbility);
	
	//Spawn the weapon actor
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Character;
	SpawnParams.Instigator = Character;
 
	// Spawn at character's location initially
	AActor* NewWeapon = World->SpawnActor<AActor>(WeaponActorClass, Character->GetActorTransform(), SpawnParams);
 
	if (NewWeapon)
	{
		
		const FName SocketName = WeaponSocket; 
			
		FAttachmentTransformRules AttachRules(
			EAttachmentRule::SnapToTarget, // Location: teleport to socket
			EAttachmentRule::SnapToTarget, // Rotation: match socket rotation
			EAttachmentRule::KeepWorld,    // Scale: keep weapon's original scale
			true                           // Weld simulated bodies
		);
 
		NewWeapon->AttachToComponent(Character->GetMesh(), AttachRules, SocketName);
		Character->EquippedWeapon= Cast<AP2C_WeaponBase>(NewWeapon);
		
	}
}
