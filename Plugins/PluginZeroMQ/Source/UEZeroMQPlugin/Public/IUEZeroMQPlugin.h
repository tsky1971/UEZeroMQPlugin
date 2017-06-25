
#pragma once

#include "ModuleManager.h"

class IUEZeroMQPlugin : public IModuleInterface
{

public:


	static inline IUEZeroMQPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked<IUEZeroMQPlugin>("UEZeroMQPlugin");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("UEZeroMQPlugin");
	}
};
