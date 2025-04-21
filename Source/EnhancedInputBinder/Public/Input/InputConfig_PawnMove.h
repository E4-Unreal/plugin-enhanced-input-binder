// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig.h"
#include "InputConfig_PawnMove.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_PawnMove : public UInputConfig
{
    GENERATED_BODY()

protected:
    virtual void OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance) override;

    virtual void Move(APawn* Pawn, const FInputActionValue& ActionValue);
};
