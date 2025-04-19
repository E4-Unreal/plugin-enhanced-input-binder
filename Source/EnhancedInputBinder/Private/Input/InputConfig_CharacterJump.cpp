// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_CharacterJump.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

void UInputConfig_CharacterJump::OnStarted_Implementation(APawn* Pawn, APlayerController* PlayerController,
    const FInputActionValue& InputActionValue)
{
    Super::OnStarted_Implementation(Pawn, PlayerController, InputActionValue);

    if (auto Character = Cast<ACharacter>(Pawn))
    {
        Character->Jump();
    }
}

void UInputConfig_CharacterJump::OnCompleted_Implementation(APawn* Pawn, APlayerController* PlayerController,
    const FInputActionValue& InputActionValue)
{
    Super::OnCompleted_Implementation(Pawn, PlayerController, InputActionValue);

    if (auto Character = Cast<ACharacter>(Pawn))
    {
        Character->StopJumping();
    }
}
