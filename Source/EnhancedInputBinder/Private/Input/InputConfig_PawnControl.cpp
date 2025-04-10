// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnControl.h"

#include "EnhancedInputComponent.h"
#include "Interfaces/PawnControlInterface.h"

TArray<uint32> UInputConfig_PawnControl::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;

    // Bind Move Action
    uint32 MoveActionHandle;
    if (BindMoveAction(EnhancedInputComponent, MoveActionHandle)) InputBindingHandles.Emplace(MoveActionHandle);

    // Bind Look Action
    uint32 LookActionHandle;
    if (BindLookAction(EnhancedInputComponent, LookActionHandle)) InputBindingHandles.Emplace(LookActionHandle);

    return InputBindingHandles;
}

bool UInputConfig_PawnControl::BindMoveAction(UEnhancedInputComponent* EnhancedInputComponent, uint32& Handle)
{
    auto OwningPawn = GetOwningPawn(EnhancedInputComponent);
    if (OwningPawn == nullptr || MoveAction == nullptr) return false;

    if (OwningPawn->GetClass()->ImplementsInterface(UPawnControlInterface::StaticClass()))
    {
        FEnhancedInputActionEventBinding& MoveActionBinding = EnhancedInputComponent->BindActionValueLambda(
            MoveAction,
            ETriggerEvent::Triggered,
            [=](const FInputActionValue& InputActionValue)
            {
                IPawnControlInterface::Execute_Move(OwningPawn, InputActionValue);
            });

        Handle = MoveActionBinding.GetHandle();
    }
    else
    {
        FEnhancedInputActionEventBinding& MoveActionBinding = EnhancedInputComponent->BindActionValueLambda(
            MoveAction,
            ETriggerEvent::Triggered,
            [OwningPawn, this](const FInputActionValue& InputActionValue)
            {
                Move(OwningPawn, InputActionValue);
            });

        Handle = MoveActionBinding.GetHandle();
    }

    return true;
}

bool UInputConfig_PawnControl::BindLookAction(UEnhancedInputComponent* EnhancedInputComponent, uint32& Handle)
{
    auto OwningPawn = GetOwningPawn(EnhancedInputComponent);
    if (OwningPawn == nullptr || LookAction == nullptr) return false;

    if (OwningPawn->GetClass()->ImplementsInterface(UPawnControlInterface::StaticClass()))
    {
        FEnhancedInputActionEventBinding& LookActionBinding = EnhancedInputComponent->BindActionValueLambda(
            LookAction,
            ETriggerEvent::Triggered,
            [=](const FInputActionValue& InputActionValue)
            {
                IPawnControlInterface::Execute_Look(OwningPawn, InputActionValue);
            });

        Handle = LookActionBinding.GetHandle();
    }
    else
    {
        FEnhancedInputActionEventBinding& LookActionBinding = EnhancedInputComponent->BindActionValueLambda(
            LookAction,
            ETriggerEvent::Triggered,
            [OwningPawn, this](const FInputActionValue& InputActionValue)
            {
                Look(OwningPawn, InputActionValue);
            });

        Handle = LookActionBinding.GetHandle();
    }

    return true;
}

void UInputConfig_PawnControl::Move(APawn* Pawn, const FInputActionValue& ActionValue)
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

void UInputConfig_PawnControl::Look(APawn* Pawn, const FInputActionValue& ActionValue)
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
