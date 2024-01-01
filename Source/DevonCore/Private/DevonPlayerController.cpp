#include "DevonPlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"

void ADevonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	PawnMappingContext = NewObject<UInputMappingContext>(this);
	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	PawnMappingContext->MapKey(MoveAction, EKeys::W);
}

