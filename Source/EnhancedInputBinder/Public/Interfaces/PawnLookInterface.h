// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnLookInterface.generated.h"

struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnLookInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class ENHANCEDINPUTBINDER_API IPawnLookInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Look(const FInputActionValue& ActionValue);
    virtual void Look_Implementation(const FInputActionValue& ActionValue);
};
