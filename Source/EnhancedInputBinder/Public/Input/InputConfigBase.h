// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputTriggers.h"
#include "InputConfigBase.generated.h"

class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionInstance;

/**
 * 입력 바인딩 전용 데이터 에셋
 */
UCLASS(Abstract)
class ENHANCEDINPUTBINDER_API UInputConfigBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    using FInputActionDelegate = TDelegate<void(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)>;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSet<ETriggerEvent> TriggerEvents;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    bool bEnableLog = false;

public:
    UInputConfigBase();

    TArray<uint32> BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    void UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    virtual void OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

    void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent, ETriggerEvent TriggerEvent, const FInputActionDelegate& InputActionDelegate, TArray<uint32>& InputBindingHandles) const;

    /* Event */

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggered(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnStarted(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnOngoing(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnCanceled(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnCompleted(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance);

    /* Query */

    UFUNCTION(BlueprintCallable)
    static APlayerController* GetPlayerController(UEnhancedInputComponent* EnhancedInputComponent);

    UFUNCTION(BlueprintCallable)
    static APawn* GetPawn(UEnhancedInputComponent* EnhancedInputComponent);

    UFUNCTION(BlueprintCallable)
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputComponent* EnhancedInputComponent);

    virtual TArray<UInputAction*> GetInputActions() const { return TArray<UInputAction*>(); }

    virtual bool IsValid() const { return !GetInputActions().IsEmpty() && !TriggerEvents.IsEmpty(); }
};
