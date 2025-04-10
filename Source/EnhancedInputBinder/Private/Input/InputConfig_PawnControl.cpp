// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PawnControl.h"

#include "EnhancedInputComponent.h"
#include "Interfaces/PawnControlInterface.h"

TArray<uint32> UInputConfig_PawnControl::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;
    auto OwningPawn = GetOwningPawn(EnhancedInputComponent);
    if (OwningPawn == nullptr) return InputBindingHandles;
    if (!OwningPawn->GetClass()->ImplementsInterface(UPawnControlInterface::StaticClass())) return InputBindingHandles;

    // Bind Move Action
    FEnhancedInputActionEventBinding& MoveActionBinding = EnhancedInputComponent->BindActionValueLambda(
                MoveAction,
                ETriggerEvent::Triggered,
                [=](const FInputActionValue& InputActionValue)
                {
                    IPawnControlInterface::Execute_Move(OwningPawn, InputActionValue);
                });

    InputBindingHandles.Emplace(MoveActionBinding.GetHandle());

    // Bind Look Action
    FEnhancedInputActionEventBinding& LookActionBinding = EnhancedInputComponent->BindActionValueLambda(
                LookAction,
                ETriggerEvent::Triggered,
                [=](const FInputActionValue& InputActionValue)
                {
                    IPawnControlInterface::Execute_Look(OwningPawn, InputActionValue);
                });

    InputBindingHandles.Emplace(LookActionBinding.GetHandle());

    return InputBindingHandles;
}
