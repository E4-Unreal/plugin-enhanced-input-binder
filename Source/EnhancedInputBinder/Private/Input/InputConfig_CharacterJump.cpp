// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_CharacterJump.h"

#include "GameFramework/Character.h"

void UInputConfig_CharacterJump::OnStarted_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnStarted_Implementation(PlayerController, InputActionInstance);

    if (auto Character = Cast<ACharacter>(PlayerController->GetPawn()))
    {
        Character->Jump();
    }
}

void UInputConfig_CharacterJump::OnCompleted_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnCompleted_Implementation(PlayerController, InputActionInstance);

    if (auto Character = Cast<ACharacter>(PlayerController->GetPawn()))
    {
        Character->StopJumping();
    }
}
