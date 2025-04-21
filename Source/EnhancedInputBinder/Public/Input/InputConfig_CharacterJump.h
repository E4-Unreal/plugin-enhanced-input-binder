// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig_PressAndRelease.h"
#include "InputConfig_CharacterJump.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_CharacterJump : public UInputConfig_PressAndRelease
{
    GENERATED_BODY()

protected:
    virtual void OnStarted_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance) override;
    virtual void OnCompleted_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance) override;
};
