// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class FiniteStateMachineEditor : ModuleRules
{
	public FiniteStateMachineEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		//OverridePackageType = PackageOverrideType.EngineDeveloper;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"FiniteStateMachine",
				"AssetTools",
				"Slate",
				"SlateCore",
				"Kismet",
				"KismetCompiler",
				"UnrealEd",
				"BlueprintGraph",
				"GraphEditor",
				"EditorStyle",
				"Projects"
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
