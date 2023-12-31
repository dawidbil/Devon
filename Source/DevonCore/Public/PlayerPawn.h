#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DEVONCORE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// collisions
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
};

