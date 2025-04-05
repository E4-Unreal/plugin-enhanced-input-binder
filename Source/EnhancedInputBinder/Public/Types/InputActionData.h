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

    bool operator==(const FInputActionData& Other) const
    {
        return Equals(Other);
    }

    bool Equals(const FInputActionData& Other) const
    {
        return InputAction == Other.InputAction && TriggerEvent == Other.TriggerEvent;
    }

    friend uint32 GetTypeHash(const FInputActionData& EquipmentSlot)
    {
        return FCrc::MemCrc32(&EquipmentSlot, sizeof(FInputActionData));
    }
};
