#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DevonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class DEVONCORE_API ADevonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	UPROPERTY()
	UInputMappingContext* PawnMappingContext;

	UPROPERTY()
	UInputAction* MoveAction;

	UPROPERTY()
	UInputAction* RotateAction;

	UPROPERTY()
	UInputAction* ShootAction;
};

