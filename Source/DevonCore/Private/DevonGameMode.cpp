#include "DevonGameMode.h"
#include "Log.h"

ADevonGameMode::ADevonGameMode() {}

void ADevonGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogDevonCore, Log, TEXT("Game is running: %s %s"), *MapName, *Options);
}

