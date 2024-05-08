// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CoreModule : ModuleRules
{
	public CoreModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
	}
}
