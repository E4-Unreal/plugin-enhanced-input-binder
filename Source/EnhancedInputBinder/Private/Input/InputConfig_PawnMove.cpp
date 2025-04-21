// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnMove.h"

#include "InputAction.h"
#include "Interfaces/PawnMoveInterface.h"

void UInputConfig_PawnMove::OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnTriggered_Implementation(PlayerController, InputActionInstance);

    auto Pawn = PlayerController->GetPawn();
    if (!Pawn) return;

    if (Pawn->Implements<UPawnMoveInterface>())
    {
        IPawnMoveInterface::Execute_Move(Pawn, InputActionInstance.GetValue());
    }
    else
    {
        Move(Pawn, InputActionInstance.GetValue());
    }
}

void UInputConfig_PawnMove::Move(APawn* Pawn, const FInputActionValue& ActionValue)
{
    // input is a Vector2D
    FVector2D MovementVector = ActionValue.Get<FVector2D>();

    if (Pawn->Controller != nullptr)
    {
        // find out which way is forward
        const FRotator Rotation = Pawn->Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // get right vector
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // add movement
        Pawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        Pawn->AddMovementInput(RightDirection, MovementVector.X);
    }
}
