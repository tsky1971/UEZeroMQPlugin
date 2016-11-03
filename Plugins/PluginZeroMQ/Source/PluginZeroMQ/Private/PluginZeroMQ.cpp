// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "PluginZeroMQPrivatePCH.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"


#include "AllowWindowsPlatformTypes.h"
#include "zmq.h"
#include "HideWindowsPlatformTypes.h"

#define LOCTEXT_NAMESPACE "FPluginZeroMQModule"

DEFINE_LOG_CATEGORY(ZeroMQLog)

void FPluginZeroMQModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(ZeroMQLog, Warning, TEXT("FPluginZeroMQModule::StartupModule()"));

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("PluginZeroMQ")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/PluginZeroMQLibrary/Win64/libzmq-v140-mt-4_2_0.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/PluginZeroMQLibrary/Mac/Release/libzmq-v140-mt-4_2_0.dylib"));
#endif // PLATFORM_WINDOWS

	ZMQHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ZMQHandle)
	{
		// Call the test function in the third party library that opens a message box
		m_ContextZMQ = zmq_ctx_new();
		if (m_ContextZMQ) {
			UE_LOG(ZeroMQLog, Warning, TEXT("FPluginZeroMQModule::StartupModule() ZeroMQ Context is ready..."));
			
		}
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load example third party library"));
	}
}

void FPluginZeroMQModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UE_LOG(ZeroMQLog, Warning, TEXT("FPluginZeroMQModule::ShutdownModule()"));

	UE_LOG(ZeroMQLog, Warning, TEXT("FPluginZeroMQModule::StartupModule() ZeroMQ Context shutdown!"));
	zmq_ctx_shutdown(m_ContextZMQ);
	m_ContextZMQ = nullptr;

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ZMQHandle);
	ZMQHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPluginZeroMQModule, PluginZeroMQ)