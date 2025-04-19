// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_Jump.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

UInputConfig_Jump::UInputConfig_Jump()
{
    TriggerEvents.Empty(2);
    TriggerEvents.Emplace(ETriggerEvent::Started);
    TriggerEvents.Emplace(ETriggerEvent::Completed);
}

void UInputConfig_Jump::OnStarted_Implementation(APawn* Pawn, APlayerController* PlayerController,
    const FInputActionValue& InputActionValue)
{
    Super::OnStarted_Implementation(Pawn, PlayerController, InputActionValue);

    if (auto Character = Cast<ACharacter>(Pawn))
    {
        Character->Jump();
    }
}

void UInputConfig_Jump::OnCompleted_Implementation(APawn* Pawn, APlayerController* PlayerController,
    const FInputActionValue& InputActionValue)
{
    Super::OnCompleted_Implementation(Pawn, PlayerController, InputActionValue);

    if (auto Character = Cast<ACharacter>(Pawn))
    {
        Character->StopJumping();
    }
}
