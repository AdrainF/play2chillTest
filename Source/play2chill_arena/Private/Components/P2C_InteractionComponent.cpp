// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/P2C_InteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "Characters/P2C_PlayerCharacter.h"
#include "Items/Weapons/P2C_WeaponBase.h"
#include "Interfaces/P2C_InteractionInterface.h"

// Sets default values for this component's properties
UP2C_InteractionComponent::UP2C_InteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UP2C_InteractionComponent::Server_Interact_Implementation()
{
	PrimaryInteract();
}

bool UP2C_InteractionComponent::Server_Interact_Validate()
{
	return true;
}

void UP2C_InteractionComponent::RequestInteract()
{
	if (!GetOwner()->HasAuthority())
	{
		Server_Interact();
	}
	else
	{
		PrimaryInteract();
	}
}

void UP2C_InteractionComponent::PrimaryInteract()
{
	TArray<struct FHitResult> OutHits;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	FCollisionShape CollisionShape;
	float Radius = SphereRadius;
	CollisionShape.SetSphere(Radius);
	FCollisionQueryParams Params;
	AP2C_PlayerCharacter* MyCharacter = Cast<AP2C_PlayerCharacter>(GetOwner());
	FVector Start = MyCharacter->FollowCamera->GetComponentLocation();
	FVector End = MyCharacter->FollowCamera->GetComponentLocation() + (MyCharacter->GetControlRotation().Vector() *
		InteractionDistance);


	Params.AddIgnoredActor(MyCharacter);
	Params.AddIgnoredActor(MyCharacter->EquippedWeapon);
	bool bBlockHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ObjectQueryParams,
	                                                    CollisionShape, Params);

	FColor LineColor = bBlockHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor->Implements<UP2C_InteractionInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyCharacter);
			IP2C_InteractionInterface::Execute_Interact(HitActor, MyPawn);

			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
			break;
		}
	}
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);
}

