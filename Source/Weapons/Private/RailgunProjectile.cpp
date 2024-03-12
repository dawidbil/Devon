#include "RailgunProjectile.h"

ARailgunProjectile::ARailgunProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15.0f);
		RootComponent = CollisionComponent;
	}
}

void ARailgunProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ARailgunProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

