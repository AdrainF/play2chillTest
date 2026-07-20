// Fill out your copyright notice in the Description page of Project Settings.


#include "System/P2C_GameplayTags.h"

#include "GameplayTagsManager.h"

FP2C_GameplayTags FP2C_GameplayTags::GameplayTags; 

void FP2C_GameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
 
	GameplayTags.AddAllTags(GameplayTagsManager);
 
	GameplayTagsManager.DoneAddingNativeTags();
}

void FP2C_GameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move, "InputTag.Move", "Move input");
	AddTag(InputTag_Look, "InputTag.Look", "Look input");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Attack, "InputTag.Attack", "Attack input");
	AddTag(InputTag_Interact, "InputTag.Interact", "Interaction input");
	AddTag(InputTag_OpenMenu, "InputTag.OpenMenu", "Open Menu");
}

void FP2C_GameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TagComment));
}
