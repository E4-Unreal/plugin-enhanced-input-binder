// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfigBase.h"
#include "InputConfig_PawnMove.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_PawnMove : public UInputConfigBase
{
    GENERATED_BODY()

protected:
    virtual void OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue) override;

    virtual void Move(APawn* Pawn, const FInputActionValue& ActionValue);
};
