#include "HoverComponent.h"
#include "Log.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/HitResult.h"
#include "CollisionQueryParams.h"
#include "Math.h"

UHoverComponent::UHoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->DebugDrawTraceTag = TraceTag;
}

void UHoverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	FHitResult Hit;
	FVector TraceStart = GetComponentLocation();
	FVector TraceEnd = GetComponentLocation() + GetForwardVector() * TraceLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.TraceTag = TraceTag;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, CollisionParams);

	if (Hit.bBlockingHit)
	{
		UStaticMeshComponent* ParentComponentMesh = Cast<UStaticMeshComponent>(GetAttachParent());
		// Force power increases as distance between body and hit object gets closer
		float DistanceScale = 1 - Hit.Time;
		UE_LOG(LogDevonCore, Log, TEXT("Pushing up (DistanceScale: %f)"), DistanceScale);
		FVector AppliedForce = Hit.ImpactNormal * DistanceScale;
		ParentComponentMesh->AddForceAtLocation(AppliedForce * PushForce, GetComponentLocation());
		DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + (AppliedForce * 150.f), 150.f, FColor::Yellow, false, 1.f, 0, 1.f);
	}
}

