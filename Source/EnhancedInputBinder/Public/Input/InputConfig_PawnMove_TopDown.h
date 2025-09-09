// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig_PawnMove.h"
#include "InputConfig_PawnMove_TopDown.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_PawnMove_TopDown : public UInputConfig_PawnMove
{
    GENERATED_BODY()

protected:
    /* InputConfig_PawnMove */

    virtual void Move(APawn* Pawn, const FInputActionValue& ActionValue) override;
};
