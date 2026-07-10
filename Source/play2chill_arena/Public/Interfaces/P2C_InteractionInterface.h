// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "P2C_InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UP2C_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAY2CHILL_ARENA_API IP2C_InteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* Interactor);
};
