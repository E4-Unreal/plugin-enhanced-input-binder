// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputConfigBase.h"
#include "InputConfig.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig : public UInputConfigBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UInputAction> InputAction;

protected:
    virtual TArray<UInputAction*> GetInputActions() const override;
};
