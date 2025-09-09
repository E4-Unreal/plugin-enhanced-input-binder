// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputConfigBase.h"
#include "InputConfig_CameraRotation.generated.h"

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfig_CameraRotation : public UInputConfigBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UInputAction> InputAction_RotateCameraLeft;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UInputAction> InputAction_RotateCameraRight;

protected:
    /* InputConfigBase */

    virtual TArray<UInputAction*> GetInputActions() const override;
    virtual void OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance) override;

    /* API */

    virtual void RotateCamera(APawn* Pawn, const FRotator& Rotation);
};
