// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnMove_TopDown.h"

void UInputConfig_PawnMove_TopDown::Move(APawn* Pawn, const FInputActionValue& ActionValue)
{
    // input is a Vector2D
    FVector2D MovementVector = ActionValue.Get<FVector2D>();

    if (APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController()))
    {
        // find out which way is forward
        const FRotator Rotation = PlayerController->PlayerCameraManager->GetCameraRotation();
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
