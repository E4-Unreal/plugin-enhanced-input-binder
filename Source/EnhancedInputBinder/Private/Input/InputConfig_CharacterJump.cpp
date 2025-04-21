// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_CharacterJump.h"

#include "GameFramework/Character.h"

void UInputConfig_CharacterJump::OnStarted_Implementation(UEnhancedInputComponent* EnhancedInputComponent,
    const FInputActionInstance& InputActionInstance)
{
    Super::OnStarted_Implementation(EnhancedInputComponent, InputActionInstance);

    if (auto Character = Cast<ACharacter>(GetPawn(EnhancedInputComponent)))
    {
        Character->Jump();
    }
}

void UInputConfig_CharacterJump::OnCompleted_Implementation(UEnhancedInputComponent* EnhancedInputComponent,
    const FInputActionInstance& InputActionInstance)
{
    Super::OnCompleted_Implementation(EnhancedInputComponent, InputActionInstance);

    if (auto Character = Cast<ACharacter>(GetPawn(EnhancedInputComponent)))
    {
        Character->StopJumping();
    }
}
