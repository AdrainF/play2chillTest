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
	FGameplayTag InputTag_Attack_Melee;
	FGameplayTag InputTag_Attack_Ranged;

protected:
	void AddAllTags(UGameplayTagsManager& Manager);

	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:
	static FP2C_GameplayTags GameplayTags;
};
