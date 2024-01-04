#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverComponent.h"
#include "DevonPlayerPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

UCLASS()
class DEVONCORE_API ADevonPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ADevonPlayerPawn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const struct FInputActionValue& ActionValue);
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverFL;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverFR;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverBL;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverBR;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere)
	float MoveScale;

};

