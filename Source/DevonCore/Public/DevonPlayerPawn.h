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

struct FInputActionValue;

UCLASS()
class DEVONCORE_API ADevonPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ADevonPlayerPawn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Tick(float DeltaSeconds);
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	/* Movement */
	void MoveBody(const FInputActionValue& ActionValue);
	void LimitVelocityToMaxSpeed();

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverFL;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverFR;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverBL;

	UPROPERTY(EditAnywhere)
	UHoverComponent* HoverBR;

	UPROPERTY(EditAnywhere)
	USceneComponent* ThrustLocation;

	UPROPERTY(EditAnywhere)
	float ForwardSpeed;

	UPROPERTY(EditAnywhere)
	float BackwardSpeed;

	UPROPERTY(EditAnywhere)
	float TurningSpeed;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	/* Fan animation */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FanMesh;

	UPROPERTY(EditAnywhere)
	float FanMaxRotationSpeed;

	UPROPERTY(EditAnywhere)
	float FanRotationAcceleration;
private:
	float FanRotationSpeed;

public:
	/* Jitter movement */
	UPROPERTY(EditAnywhere)
	float JitterMovementFrequency;

	UPROPERTY(EditAnywhere)
	float JitterMovementAmplitude;

private:
	float JitterMovementTime;

public:
	/* Weapon */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponBase;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponTurret;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponGun;

	void MoveTurret(const float InputYaw);
	void MoveGun(const float InputPitch);
	void FireGun(const FInputActionValue& ActionValue);

	UPROPERTY(EditAnywhere)
	float WeaponPitchClampAngleUp;

	UPROPERTY(EditAnywhere)
	float WeaponPitchClampAngleDown;

	UPROPERTY(EditAnywhere)
	float WeaponYawClampAngle;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ARailgunProjectile> ProjectileClass;

public:
	/* Input */
	void HandleRotateAction(const FInputActionValue& ActionValue);
	void ScaleInput(FVector* Input);
};

