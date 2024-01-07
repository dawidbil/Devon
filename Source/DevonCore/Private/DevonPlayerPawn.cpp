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

ADevonPlayerPawn::ADevonPlayerPawn()
{
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionMesh"));
	SetRootComponent(CollisionMesh);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(CollisionMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CollisionMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

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

	ForwardSpeed = 10.f;
	BackwardSpeed = 2.f;
	TurningSpeed = 2.f;
}

void ADevonPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ADevonPlayerController* DPC = Cast<ADevonPlayerController>(Controller);
	check(EIC && DPC);
	EIC->BindAction(DPC->MoveAction, ETriggerEvent::Triggered, this, &ADevonPlayerPawn::Move);
	EIC->BindAction(DPC->BumpUpwardsAction, ETriggerEvent::Triggered, this, &ADevonPlayerPawn::BumpUpwards);

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

void ADevonPlayerPawn::Move(const FInputActionValue& ActionValue)
{
	UE_LOG(LogDevonCore, Log, TEXT("ADevonPlayerPawn::Move"));

	FVector Input = ActionValue.Get<FInputActionValue::Axis3D>();
	ScaleInput(&Input);
	FVector AppliedForce = GetActorRotation().RotateVector(Input) * CollisionMesh->GetMass();
	CollisionMesh->AddForceAtLocation(AppliedForce, ThrustLocation->GetComponentLocation());
	DrawDebugDirectionalArrow(GetWorld(), ThrustLocation->GetComponentLocation(), ThrustLocation->GetComponentLocation() + AppliedForce, 150.f, FColor::Blue, false, 1.f, 0, 1.f);
}

void ADevonPlayerPawn::BumpUpwards(const FInputActionValue& ActionValue)
{
	UE_LOG(LogDevonCore, Log, TEXT("ADevonPlayerPawn::BumpUpwards"));
	CollisionMesh->AddForce(FVector::UpVector * CollisionMesh->GetMass());
}

