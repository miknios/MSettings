// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MSettings : ModuleRules
{
	public MSettings(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CommonUI",
				"UMG",
				"DeveloperSettings",
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore",
				"CommonInput",
				"ApplicationCore"
			}
		);
	}
}
