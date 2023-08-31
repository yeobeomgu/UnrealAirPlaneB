// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Remake_PlaneShoot : ModuleRules
{
	public Remake_PlaneShoot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
