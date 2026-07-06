// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "P2C_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PLAY2CHILL_ARENA_API UP2C_AssetManager : public UAssetManager
{
	GENERATED_BODY()

	UP2C_AssetManager();
 
	// Returns the AssetManager singleton object.
	static UP2C_AssetManager& Get();
 
protected:
 
	virtual void StartInitialLoading() override;
};
