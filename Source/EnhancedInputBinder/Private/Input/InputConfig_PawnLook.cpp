// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnLook.h"

#include "Interfaces/PawnLookInterface.h"

void UInputConfig_PawnLook::OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController,
                                                       const FInputActionValue& InputActionValue)
{
    Super::OnTriggered_Implementation(Pawn, PlayerController, InputActionValue);

    if (!Pawn) return;

    if (Pawn->Implements<UPawnLookInterface>())
    {
        IPawnLookInterface::Execute_Look(Pawn, InputActionValue);
    }
    else
    {
        Look(Pawn, InputActionValue);
    }
}

void UInputConfig_PawnLook::Look(APawn* Pawn, const FInputActionValue& ActionValue)
{
    // input is a Vector2D
    FVector2D LookAxisVector = ActionValue.Get<FVector2D>();

    if (Pawn->Controller != nullptr)
    {
        // add yaw and pitch input to controller
        Pawn->AddControllerYawInput(LookAxisVector.X);
        Pawn->AddControllerPitchInput(LookAxisVector.Y);
    }
}
