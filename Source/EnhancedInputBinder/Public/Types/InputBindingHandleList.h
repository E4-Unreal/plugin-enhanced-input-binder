// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputBindingHandleList.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FInputBindingHandleList
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> Handles;

    FInputBindingHandleList() {}

    FInputBindingHandleList(const TArray<uint32>& InHandles)
    {
        Handles.Empty(InHandles.Num());
        for (uint32 Handle : InHandles)
        {
            Handles.Emplace(Handle);
        }
    }
};
