// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IUEZeroMQPlugin.h"

// @third party code - BEGIN
#include "AllowWindowsPlatformTypes.h"
#include "oscpkt.hh"
#include "zmq.h"
#include "czmq.h"
#include "HideWindowsPlatformTypes.h"
// @third party code - END

class FUEZeroMQPluginModule : public IUEZeroMQPlugin
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	bool SearchForDllPath(FString _searchBase, FString _dllName);

private:
	/** Handle to the test dll we will load */
	void*	ZMQLibraryHandle;

};