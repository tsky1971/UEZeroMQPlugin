// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UEZeroMQPlugin.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"
#include "ZMQLibrary.h"


#define LOCTEXT_NAMESPACE "FUEZeroMQPluginModule"


bool FUEZeroMQPluginModule::SearchForDllPath(FString _searchBase, FString _dllName)
{
	//Search Plugins folder for an instance of Dll.dll, and add to platform search path
	TArray<FString> directoriesToSkip;
	IPlatformFile &PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
	PlatformFile.IterateDirectory(*_searchBase, Visitor);

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString file = TimestampIt.Key();
		const FString filePath = FPaths::GetPath(file);
		const FString fileName = FPaths::GetCleanFilename(file);
		if (fileName.Compare(_dllName) == 0)
		{
			FPlatformProcess::AddDllDirectory(*filePath); // only load dll when needed for use. Broken with 4.11.
			FPlatformProcess::GetDllHandle(*file); // auto-load dll with plugin - needed as 4.11 breaks above line.
			return true;
		}
	}
	return false;
}


void FUEZeroMQPluginModule::StartupModule()
{
	
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("UEZeroMQPlugin")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UEZeroMQPluginLibrary/x64/Release/ZMQLibrary.dll"));
#elif PLATFORM_MAC
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/UEZeroMQPluginLibrary/Mac/Release/libZMQLibrary.dylib"));
#endif // PLATFORM_WINDOWS

	ZMQLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ZMQLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		//ZMQLibraryFunction();
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load ZMQ third party library"));
		UE_LOG(LogInit, Log, TEXT("ZMQLibraryHandle is NOT valid"));
	}

	FString dllName = "libzmq.dll";
	if (SearchForDllPath(FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/libzmq/x64/Release/v140/dynamic/")), dllName))
	{
		UE_LOG(LogInit, Log, TEXT("SearchForDllPath libzmq SUCCESSFUL"));
	}
	else
	{
		//Stop loading - plugin required DLL to load successfully
		checkf(false, TEXT("Failed to load libzmq"));
	}

	dllName = "libczmq.dll";
	if (SearchForDllPath(FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/libczmq/x64/Release/v140/dynamic/")), dllName))
	{
		UE_LOG(LogInit, Log, TEXT("SearchForDllPath libczmq SUCCESSFUL"));
	}
	else
	{
		//Stop loading - plugin required DLL to load successfully
		checkf(false, TEXT("Failed to load libczmq"));
	}

	dllName = "libsodium.dll";
	if (SearchForDllPath(FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/libsodium/x64/Release/v140/dynamic/")), dllName))
	{
		UE_LOG(LogInit, Log, TEXT("SearchForDllPath libsodium SUCCESSFUL"));
	}
	else
	{
		//Stop loading - plugin required DLL to load successfully
		checkf(false, TEXT("Failed to load libsodium"));
	}

}

void FUEZeroMQPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ZMQLibraryHandle);
	ZMQLibraryHandle = nullptr;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEZeroMQPluginModule, UEZeroMQPlugin)