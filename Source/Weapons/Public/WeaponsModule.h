#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FWeapons : public IModuleInterface
{
public:
	static inline FWeapons& Get()
	{
		return FModuleManager::LoadModuleChecked<FWeapons>("Weapons");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Weapons");
	}

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

