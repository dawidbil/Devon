#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "RailgunProjectile.generated.h"

UCLASS()
class WEAPONS_API ARailgunProjectile : public AActor
{
	GENERATED_BODY()

public:
	ARailgunProjectile();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

protected:
	virtual void BeginPlay() override;
};

