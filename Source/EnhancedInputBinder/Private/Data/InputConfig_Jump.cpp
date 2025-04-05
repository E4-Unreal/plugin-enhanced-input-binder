// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputConfig_Jump.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

TArray<uint32> UInputConfig_Jump::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;
    auto PlayerController = GetOwningPlayer(EnhancedInputComponent);
    auto PlayerCharacter = PlayerController->GetCharacter();
    if (PlayerCharacter == nullptr) return InputBindingHandles;

    FEnhancedInputActionEventBinding& JumpBinding = EnhancedInputComponent->BindAction(
                JumpAction,
                ETriggerEvent::Started,
                this,
                &ThisClass::Jump,
                PlayerCharacter
                );

    InputBindingHandles.Emplace(JumpBinding.GetHandle());

    FEnhancedInputActionEventBinding& StopJumpBinding = EnhancedInputComponent->BindAction(
               JumpAction,
               ETriggerEvent::Started,
               this,
               &ThisClass::StopJumping,
               PlayerCharacter
               );

    InputBindingHandles.Emplace(StopJumpBinding.GetHandle());

    return InputBindingHandles;
}

void UInputConfig_Jump::Jump(ACharacter* Character)
{
    if (Character == nullptr) return;

    Character->Jump();
}

void UInputConfig_Jump::StopJumping(ACharacter* Character)
{
    if (Character == nullptr) return;

    Character->StopJumping();
}
