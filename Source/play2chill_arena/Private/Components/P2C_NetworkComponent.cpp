// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/P2C_NetworkComponent.h"

#include "Characters/P2C_PlayerCharacter.h"
#include "Components/P2C_InteractionComponent.h"
#include "Core/P2C_ArenaGameMode.h"
#include "Items/Data/MyP2C_WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
UP2C_NetworkComponent::UP2C_NetworkComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(true);
}

// Called when the game starts
void UP2C_NetworkComponent::BeginPlay()
{
	Super::BeginPlay();
	
	P2C_PlayerCharacter =Cast<AP2C_PlayerCharacter>(GetOwner());
	
}

void UP2C_NetworkComponent::Server_SpawnProjectile_Implementation(TSubclassOf<AActor> ProjectileClass, FVector Location,
	FRotator Rotation)
{
	if (!ProjectileClass) return;
	 APawn* SpawnedPawn = Cast<APawn>(GetOwner());
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = SpawnedPawn;
	SpawnParams.Owner = SpawnedPawn;
 
	GetWorld()->SpawnActor<AActor>(ProjectileClass, Location, Rotation, SpawnParams);
}

bool UP2C_NetworkComponent::Server_SpawnProjectile_Validate(TSubclassOf<AActor> ProjectileClass, FVector Location,
	FRotator Rotation)
{
	return true;
}

void UP2C_NetworkComponent::Request_SpawnProjectile(TSubclassOf<AActor> ProjectileClass, FVector Location,
	FRotator Rotation)
{
	if (GetOwner()->HasAuthority())
	{	
		GetWorld()->SpawnActor<AActor>(ProjectileClass, Location, Rotation);
	}
	else
	{
		Server_SpawnProjectile(ProjectileClass, Location, Rotation);
	}
}

void UP2C_NetworkComponent::Request_PlayAttack(UAnimMontage* Montage)
{
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (GetOwner()->HasAuthority())
	{
		
		PlayerCharacter->PlayAnimMontage(Montage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Request_palyAnim klient"));
		Server_PlayAttack(Montage);
	}
}

void UP2C_NetworkComponent::Server_PlayAttack_Implementation(UAnimMontage* Montage)
{
	UE_LOG(LogTemp, Warning, TEXT("Request_palyAnim server"));
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());

	PlayerCharacter->PlayAnimMontage(Montage);
}

bool UP2C_NetworkComponent::Server_PlayAttack_Validate(UAnimMontage* Montage)
{
	return true;
}

void UP2C_NetworkComponent::Server_RequestRespawn_Implementation()
{
	 AP2C_ArenaGameMode* GM = GetWorld()->GetAuthGameMode<AP2C_ArenaGameMode>();
     
	 if (GM)
	 {
	 	GM->RequestRespawn(GetController());
	 	
		 ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
		if (PlayerCharacter)
		{
			PlayerCharacter->Destroy();
		}
	 }
}

AController* UP2C_NetworkComponent::GetController()
{
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn)
	{
		return OwningPawn->GetController();
	}
	return nullptr;
}

