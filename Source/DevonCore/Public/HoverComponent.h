#pragma once

#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/NameTypes.h"
#include "HoverComponent.generated.h"

UCLASS(BluePrintable)
class DEVONCORE_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHoverComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);

	UPROPERTY(EditAnywhere)
	float TraceLength = 100.f;

	UPROPERTY(EditAnywhere)
	float PushForce = 100.f;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_WorldStatic;

	FName TraceTag = FName(TEXT("HoverComponentTrace"));
};

