// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PluginZeroMQ : ModuleRules
{
	public PluginZeroMQ(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"PluginZeroMQ/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"PluginZeroMQ/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "CoreUObject",
                "Sockets",
                "Networking",
                "RHI",
                "RenderCore",
                "Renderer",
                "ShaderCore",
                "HeadMountedDisplay",
                "Slate",
                "SlateCore",
                "PluginZeroMQLibrary",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
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
