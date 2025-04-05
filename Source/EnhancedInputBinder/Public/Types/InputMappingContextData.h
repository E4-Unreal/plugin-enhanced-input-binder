// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContextData.generated.h"

class UInputMappingContext;

USTRUCT(Atomic, BlueprintType)
struct ENHANCEDINPUTBINDER_API FInputMappingContextData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Priority;
};
