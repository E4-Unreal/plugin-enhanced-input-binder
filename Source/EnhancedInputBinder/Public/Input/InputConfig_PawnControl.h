// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig.h"
#include "InputConfig_PawnControl.generated.h"

class UInputAction;
struct FInputActionValue;
struct FEnhancedInputActionEventBinding;

/**
 *
 */
UCLASS(meta = (DisplayName = "InputConfig_PawnControl"))
class ENHANCEDINPUTBINDER_API UInputConfig_PawnControl : public UInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UInputAction> LookAction;

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;

    virtual bool BindMoveAction(UEnhancedInputComponent* EnhancedInputComponent, uint32& Handle);
    virtual bool BindLookAction(UEnhancedInputComponent* EnhancedInputComponent, uint32& Handle);

    virtual void Move(APawn* Pawn, const FInputActionValue& ActionValue);
    virtual void Look(APawn* Pawn, const FInputActionValue& ActionValue);
};
