// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/InputMappingContextData.h"
#include "InputConfig.generated.h"

class UEnhancedInputLocalPlayerSubsystem;

/**
 * 입력 바인딩 전용 데이터 에셋
 */
UCLASS(Abstract)
class ENHANCEDINPUTBINDER_API UInputConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (DisplayPriority = 0))
    FInputMappingContextData InputMappingContextData;

public:
    TArray<uint32> BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    void UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    static APawn* GetOwningPawn(UEnhancedInputComponent* EnhancedInputComponent);
    static ACharacter* GetOwningCharacter(UEnhancedInputComponent* EnhancedInputComponent);
    static APlayerController* GetOwningPlayerController(UEnhancedInputComponent* EnhancedInputComponent);
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputComponent* EnhancedInputComponent);

    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) { return TArray<uint32>(); }
    virtual void OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

    virtual void AddMappingContext(UEnhancedInputComponent* EnhancedInputComponent);
    virtual void RemoveMappingContext(UEnhancedInputComponent* EnhancedInputComponent);
};
