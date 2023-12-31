#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DevonGameMode.generated.h"

UCLASS()
class DEVONCORE_API ADevonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADevonGameMode();
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
};

