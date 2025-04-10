// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnControlInterface.generated.h"

struct FInputActionValue;
class UInputAction;

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class ENHANCEDINPUTBINDER_API UPawnControlInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class ENHANCEDINPUTBINDER_API IPawnControlInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Move(FInputActionValue ActionValue);
    virtual void Move_Implementation(FInputActionValue ActionValue);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Look(FInputActionValue ActionValue);
    virtual void Look_Implementation(FInputActionValue ActionValue);
};
