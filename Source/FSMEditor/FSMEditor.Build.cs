// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class FSMEditor : ModuleRules
{
	public FSMEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		OverridePackageType = PackageOverrideType.EngineDeveloper;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"FSM",
			"AssetTools",
			"Slate",
			"SlateCore",
			"Kismet",
			"KismetCompiler",
			"UnrealEd",
			"BlueprintGraph",
			"GraphEditor",
			"EditorStyle"
		});
	}
}
