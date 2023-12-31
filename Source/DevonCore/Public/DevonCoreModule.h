#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FDevonCore : public IModuleInterface
{
public:
	static inline FDevonCore& Get()
	{
		return FModuleManager::LoadModuleChecked<FDevonCore>("DevonCore");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("DevonCore");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

