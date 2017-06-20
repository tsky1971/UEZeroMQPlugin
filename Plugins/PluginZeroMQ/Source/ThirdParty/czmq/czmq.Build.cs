// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class czmq : ModuleRules
{
	public czmq(TargetInfo Target)
	{
		Type = ModuleType.External;

		string includePath = Path.Combine(ModuleDirectory, "include");
        PublicIncludePaths.AddRange(new string[] { includePath });

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "bin", "x64", "Release", "v140", "dynamic"));
			PublicAdditionalLibraries.Add("czmq.lib");

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("czmq.dll");
		}
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "czmq.dylib"));
        }
	}
}
