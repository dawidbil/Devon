#include "WeaponsModule.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FWeapons::StartupModule()
{
	UE_LOG(LogWeapons, Log, TEXT("Weapons module starting up"));
}

void FWeapons::ShutdownModule()
{
	UE_LOG(LogWeapons, Log, TEXT("Weapons module shutting down"));
}

IMPLEMENT_MODULE( FWeapons, Weapons );


