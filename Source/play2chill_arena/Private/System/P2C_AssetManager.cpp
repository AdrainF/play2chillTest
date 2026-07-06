// Fill out your copyright notice in the Description page of Project Settings.


#include "System/P2C_AssetManager.h"

#include "System/P2C_GameplayTags.h"

UP2C_AssetManager::UP2C_AssetManager()
{
}

UP2C_AssetManager& UP2C_AssetManager::Get()
{
	check(GEngine);
 
	UP2C_AssetManager* MyAssetManager = Cast<UP2C_AssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UP2C_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FP2C_GameplayTags::InitializeNativeTags();
}
