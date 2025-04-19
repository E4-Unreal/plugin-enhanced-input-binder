// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputTriggers.h"
#include "InputConfig.generated.h"

class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;

/**
 * 입력 바인딩 전용 데이터 에셋
 */
UCLASS(Abstract)
class ENHANCEDINPUTBINDER_API UInputConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UInputAction> InputAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSet<ETriggerEvent> TriggerEvents;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    bool bEnableLog;

public:
    UInputConfig();

    TArray<uint32> BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    void UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    virtual void OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

    uint32 BindTriggeredEvent(UEnhancedInputComponent* EnhancedInputComponent);
    uint32 BindStartedEvent(UEnhancedInputComponent* EnhancedInputComponent);
    uint32 BindOngoingEvent(UEnhancedInputComponent* EnhancedInputComponent);
    uint32 BindCanceledEvent(UEnhancedInputComponent* EnhancedInputComponent);
    uint32 BindCompletedEvent(UEnhancedInputComponent* EnhancedInputComponent);

    UFUNCTION(BlueprintNativeEvent)
    void OnTriggered(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnStarted(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnOngoing(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnCanceled(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue);

    UFUNCTION(BlueprintNativeEvent)
    void OnCompleted(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue);

    UFUNCTION(BlueprintCallable)
    static APawn* GetOwningPawn(UEnhancedInputComponent* EnhancedInputComponent);

    UFUNCTION(BlueprintCallable)
    static APlayerController* GetOwningPlayerController(UEnhancedInputComponent* EnhancedInputComponent);

    UFUNCTION(BlueprintCallable)
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputComponent* EnhancedInputComponent);
};
