// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig.h"
#include "InputConfig_CharacterJump.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_CharacterJump : public UInputConfig
{
    GENERATED_BODY()

public:
    UInputConfig_CharacterJump();

protected:
    virtual void OnStarted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue) override;
    virtual void OnCompleted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue) override;
};
