// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P2C_NetworkComponent.generated.h"

class AP2C_PlayerCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY2CHILL_ARENA_API UP2C_NetworkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UP2C_NetworkComponent();

protected:
	UPROPERTY()
	AP2C_PlayerCharacter* P2C_PlayerCharacter;
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SpawnProjectile(TSubclassOf<AActor> ProjectileClass, FVector Location, FRotator Rotation);
	UFUNCTION(BlueprintCallable, Category = "SpawnProjectile")
	void Request_SpawnProjectile(TSubclassOf<AActor> ProjectileClass, FVector Location, FRotator Rotation);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlayAttack(UAnimMontage* Montage);

	UFUNCTION(BlueprintCallable, Category = "PlayMontage")
	void Request_PlayAttack(UAnimMontage* Montage);

	UFUNCTION(Server, Reliable)
	void Server_RequestRespawn();
	
	AController* GetController();
};
