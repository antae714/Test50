// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FSM : ModuleRules
{
	public FSM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
	}
}