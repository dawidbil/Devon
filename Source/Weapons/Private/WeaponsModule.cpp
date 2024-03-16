#include "DevonCoreModule.h"
#include "Modules/ModuleManager.h"

#include "Log.h"

void FDevonCore::StartupModule()
{
	UE_LOG(LogDevonCore, Log, TEXT("DevonCore module starting up"));
}

void FDevonCore::ShutdownModule()
{
	UE_LOG(LogDevonCore, Log, TEXT("DevonCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE( FDevonCore, DevonCore, "DevonCore" );


