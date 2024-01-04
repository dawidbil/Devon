#include "HoverComponent.h"
#include "Log.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/HitResult.h"
#include "CollisionQueryParams.h"

UHoverComponent::UHoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
}

void UHoverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	FHitResult Hit;
	FVector TraceStart = GetComponentLocation();
	FVector TraceEnd = GetComponentLocation() + GetForwardVector() * TraceLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;

	GetWorld()->DebugDrawTraceTag = TraceTag;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, CollisionParams);

	if (Hit.bBlockingHit)
	{
		UE_LOG(LogDevonCore, Log, TEXT("Hit at distance %f, Location: %s"), Hit.Distance, *Hit.Location.ToString());
	}
}

