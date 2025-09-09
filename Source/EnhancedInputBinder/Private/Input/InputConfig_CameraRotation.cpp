// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_CameraRotation.h"

#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"

TArray<UInputAction*> UInputConfig_CameraRotation::GetInputActions() const
{
    TArray<UInputAction*> InputActions;
    InputActions.Emplace(InputAction_RotateCameraLeft);
    InputActions.Emplace(InputAction_RotateCameraRight);

    return InputActions;
}

void UInputConfig_CameraRotation::OnTriggered_Implementation(APlayerController* PlayerController,
                                                             const FInputActionInstance& InputActionInstance)
{
    if (APawn* Pawn = PlayerController->GetPawn())
    {
        const UInputAction* InputAction = InputActionInstance.GetSourceAction();

        if (InputAction == InputAction_RotateCameraLeft)
        {
            FRotator Rotator = FRotator(0, -90, 0);
            RotateCamera(Pawn, Rotator);
        }
        else if (InputAction == InputAction_RotateCameraRight)
        {
            FRotator Rotator = FRotator(0, 90, 0);
            RotateCamera(Pawn, Rotator);
        }
    }
}

void UInputConfig_CameraRotation::RotateCamera(APawn* Pawn, const FRotator& Rotation)
{
    if (USpringArmComponent* SpringArm = Pawn->GetComponentByClass<USpringArmComponent>())
    {
        FRotator OldRotation = SpringArm->GetRelativeRotation();
        FRotator NewRotation = OldRotation + Rotation;
        SpringArm->SetRelativeRotation(NewRotation);
    }
}
