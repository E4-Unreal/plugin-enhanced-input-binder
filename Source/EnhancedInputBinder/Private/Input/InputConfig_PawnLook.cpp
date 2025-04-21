// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnLook.h"

#include "InputAction.h"
#include "Interfaces/PawnLookInterface.h"

void UInputConfig_PawnLook::OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnTriggered_Implementation(PlayerController, InputActionInstance);

    auto Pawn = PlayerController->GetPawn();
    if (!Pawn) return;

    if (Pawn->Implements<UPawnLookInterface>())
    {
        IPawnLookInterface::Execute_Look(Pawn, InputActionInstance.GetValue());
    }
    else
    {
        Look(Pawn, InputActionInstance.GetValue());
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
