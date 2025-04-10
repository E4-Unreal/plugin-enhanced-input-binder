// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig.h"
#include "InputConfig_Jump.generated.h"

class UInputAction;

/**
 *
 */
UCLASS(meta = (DisplayName = "InputConfig_Jump"))
class ENHANCEDINPUTBINDER_API UInputConfig_Jump : public UInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UInputAction> JumpAction;

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;

    virtual void Jump(ACharacter* Character);

    virtual void StopJumping(ACharacter* Character);
};
