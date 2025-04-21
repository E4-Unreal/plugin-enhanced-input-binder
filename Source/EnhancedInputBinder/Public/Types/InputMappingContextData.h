// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputMappingContextData.generated.h"

class UInputMappingContext;

USTRUCT(Atomic, BlueprintType)
struct FInputMappingContextData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Priority;
};
