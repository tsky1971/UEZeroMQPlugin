// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEZeroMQPlugin : ModuleRules
{
    public UEZeroMQPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicIncludePaths.AddRange(
            new string[] {
                "UEZeroMQPlugin/Public"
                // ... add public include paths required here ...
            }
            );
                
        
        PrivateIncludePaths.AddRange(
            new string[] {
                "UEZeroMQPlugin/Private",
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
                //"UEZeroMQPluginLibrary",
                "libsodium",
                "libzmq",
                "czmq",
                "cppzmq",
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
