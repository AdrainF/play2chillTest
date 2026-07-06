// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/P2C_InputConfig.h"

const UInputAction* UP2C_InputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& TaggedInputAction : TaggedInputActions)
{
	if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
	{
		return TaggedInputAction.InputAction;
	}
}
 
	return nullptr;
}
