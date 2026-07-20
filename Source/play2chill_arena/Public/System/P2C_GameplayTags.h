// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * 
 */
class UGameplayTagsManager;

struct FP2C_GameplayTags
{
	public:
	static const FP2C_GameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();
	//Tags
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_Attack;
	FGameplayTag InputTag_Interact;
	FGameplayTag InputTag_OpenMenu;

protected:
	// Adds all defined tags to the provided GameplayTagsManager
	void AddAllTags(UGameplayTagsManager& Manager);
	// Adds a single tag to the provided GameplayTagsManager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FP2C_GameplayTags GameplayTags;
};
