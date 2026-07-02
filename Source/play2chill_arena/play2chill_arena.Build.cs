// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class play2chill_arena : ModuleRules
{
	public play2chill_arena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			
			//modules for online multiplayer
			"OnlineSubsystem", 
			"OnlineSubsystemUtils",
			
			//modules for gameplay ability system
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
