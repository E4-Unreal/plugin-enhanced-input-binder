// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnMoveInterface.generated.h"

struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnMoveInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class ENHANCEDINPUTBINDER_API IPawnMoveInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Move(const FInputActionValue& ActionValue);
    virtual void Move_Implementation(const FInputActionValue& ActionValue);
};
