// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P2C_InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAY2CHILL_ARENA_API UP2C_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UP2C_InteractionComponent();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float SphereRadius=30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance=500.0f;
	

public:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interact();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RequestInteract();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void PrimaryInteract();
};
