// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputActionData.generated.h"

class UInputAction;

USTRUCT(Atomic, BlueprintType)
struct ENHANCEDINPUTBINDER_API FInputActionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputAction> InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETriggerEvent TriggerEvent = ETriggerEvent::Triggered;

    FORCEINLINE bool IsValid() const { return InputAction && TriggerEvent != ETriggerEvent::None; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }
};
