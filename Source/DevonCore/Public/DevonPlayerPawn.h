#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HoverComponent.h"
#include "DevonPlayerPawn.generated.h"

class UStaticMeshComponent;
class USceneComponent;
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
	void ScaleInput(FVector* Input);
	void Move(const struct FInputActionValue& ActionValue);
	void BumpUpwards(const struct FInputActionValue& ActionValue);
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CollisionMesh;

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
	float ForwardSpeed;

	UPROPERTY(EditAnywhere)
	float BackwardSpeed;

	UPROPERTY(EditAnywhere)
	float TurningSpeed;

	UPROPERTY(EditAnywhere)
	USceneComponent* ThrustLocation;
};

