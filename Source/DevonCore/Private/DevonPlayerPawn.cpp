#include "DevonPlayerPawn.h"
#include "DevonPlayerController.h"
#include "HoverComponent.h"
#include "Log.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Math/Vector.h"

ADevonPlayerPawn::ADevonPlayerPawn()
{
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionMesh"));
	SetRootComponent(CollisionMesh);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(CollisionMesh);

	HoverFL = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverFL"));
	HoverFL->SetupAttachment(CollisionMesh);

	HoverFR = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverFR"));
	HoverFR->SetupAttachment(CollisionMesh);

	HoverBL = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverBL"));
	HoverBL->SetupAttachment(CollisionMesh);

	HoverBR = CreateDefaultSubobject<UHoverComponent>(TEXT("HoverBR"));
	HoverBR->SetupAttachment(CollisionMesh);

	ThrustLocation = CreateDefaultSubobject<USceneComponent>(TEXT("ThrustLocation"));
	ThrustLocation->SetupAttachment(CollisionMesh);

	WeaponBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBase"));
	WeaponBase->SetupAttachment(CollisionMesh);

	WeaponTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponTurret"));
	WeaponTurret->SetupAttachment(WeaponBase);

	WeaponGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponGun"));
	WeaponGun->SetupAttachment(WeaponTurret);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(WeaponGun);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	ForwardSpeed = 10.f;
	BackwardSpeed = 2.f;
	TurningSpeed = 2.f;
	MaxSpeed = 100.f;

	FanMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FanMesh"));
	FanMesh->SetupAttachment(Body);
	FanMaxRotationSpeed = 10.f;
	FanRotationAcceleration = 1.f;
	FanRotationSpeed = 0.f;

	JitterMovementFrequency = 100.f;
	JitterMovementAmplitude = 1.f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void ADevonPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ADevonPlayerController* DPC = Cast<ADevonPlayerController>(Controller);
	check(EIC && DPC);
	EIC->BindAction(DPC->MoveAction, ETriggerEvent::Triggered, this, &ADevonPlayerPawn::Move);

	ULocalPlayer* LocalPlayer = DPC->GetLocalPlayer();
	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DPC->PawnMappingContext, 0);
}

void ADevonPlayerPawn::ScaleInput(FVector* Input)
{
	Input->X *= Input->X > 0 ? ForwardSpeed : BackwardSpeed;
	Input->Y *= TurningSpeed;
}

void ADevonPlayerPawn::MoveBody(const FInputActionValue& ActionValue)
{
	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	// Rotate fan before scaling
	UE_LOG(LogDevonCore, Log, TEXT("Adding to FanRotationSpeed: %f"), Input.X * FanRotationAcceleration);
	FanRotationSpeed += Input.X * FanRotationAcceleration;
	// Scale & apply force to body
	ScaleInput(&Input);
	FVector AppliedForce = GetActorRotation().RotateVector(Input) * CollisionMesh->GetMass();
	CollisionMesh->AddForceAtLocation(AppliedForce, ThrustLocation->GetComponentLocation());
}

float VectorSquaredValuesSum(const FVector* Vector)
{
	return FMath::Pow(Vector->X, 2.f) + FMath::Pow(Vector->Y, 2.f) + FMath::Pow(Vector->Z, 2.f);
}

void ADevonPlayerPawn::LimitVelocityToMaxSpeed()
{
	FVector Velocity = CollisionMesh->GetPhysicsLinearVelocity();
	// UE_LOG(LogDevonCore, Log, TEXT("Current Speed: %f"), Velocity.Size());
	if (Velocity.Size() <= MaxSpeed)
	{
		return;
	}
	float LimitFactor = FMath::Pow(MaxSpeed, 2.f) / VectorSquaredValuesSum(&Velocity);
	FVector LimitedVelocity = Velocity * LimitFactor;
	// UE_LOG(LogDevonCore, Log, TEXT("Limited Speed: %f"), LimitedVelocity.Size());
	CollisionMesh->SetPhysicsLinearVelocity(LimitedVelocity);
}

void ADevonPlayerPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LimitVelocityToMaxSpeed();
	
	// Hovercraft mesh jitter movement
	JitterMovementTime += DeltaSeconds;
	// Jitter is only visible when vehicle is moving slowly
	float JitterMovementScale = 1 - (CollisionMesh->GetPhysicsLinearVelocity().Size() / MaxSpeed);
	float JitterMovementCurrent = FMath::Sin(JitterMovementTime * JitterMovementFrequency) * JitterMovementAmplitude * JitterMovementScale;
	Body->SetRelativeLocation(FVector(0.f, JitterMovementCurrent, JitterMovementCurrent));

	// Fan mesh animation
	FRotator Rotation = FanMesh->GetRelativeRotation();
	Rotation.Roll += FanRotationSpeed;
	if (FanRotationSpeed > FanMaxRotationSpeed)
	{
		FanRotationSpeed = FanMaxRotationSpeed;
	}
	if (FanRotationSpeed < -FanMaxRotationSpeed)
	{
		FanRotationSpeed = -FanMaxRotationSpeed;
	}
	if (FanRotationSpeed > 0)
	{
		FanRotationSpeed -= FanRotationAcceleration / 2;
		if (FanRotationSpeed < 0)
		{
			FanRotationSpeed = 0;
		}
	}
	else if (FanRotationSpeed < 0)
	{
		FanRotationSpeed += FanRotationAcceleration / 2;
		if (FanRotationSpeed > 0)
		{
			FanRotationSpeed = 0;
		}
	}
	UE_LOG(LogDevonCore, Log, TEXT("FanRotationSpeed: %f"), FanRotationSpeed);
	UE_LOG(LogDevonCore, Log, TEXT("Rotation Roll: %f"), Rotation.Roll);
	FanMesh->SetRelativeRotation(Rotation);
}

void ADevonPlayerPawn::MoveTurret(const FInputActionValue& ActionValue)
{
	FRotator Input(ActionValue[0], ActionValue[1], ActionValue[2]);
	UE_LOG(LogDevonCore, Log, TEXT("Received FInputActionValue: %s"), *Input.ToString());
	Input += WeaponTurret->GetRelativeRotation();
	UE_LOG(LogDevonCore, Log, TEXT("Setting relative rotation: %s"), *Input.ToString());
	WeaponTurret->SetRelativeRotation(Input);
}

