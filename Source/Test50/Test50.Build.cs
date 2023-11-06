// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Test50 : ModuleRules
{
	public Test50(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
			"FSM"
		});
	}
}
