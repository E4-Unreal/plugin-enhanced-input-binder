// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfig.h"
#include "Types/InputActionData.h"
#include "InputConfig_ToggleWidget.generated.h"

/**
 *
 */
UCLASS(meta = (DisplayName = "InputConfig_ToggleWidget"))
class ENHANCEDINPUTBINDER_API UInputConfig_ToggleWidget : public UInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly)
    TMap<FInputActionData, TSubclassOf<UUserWidget>> InputActionMap;

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) override;

    virtual void ToggleWidget(UUserWidget* Widget);
};
