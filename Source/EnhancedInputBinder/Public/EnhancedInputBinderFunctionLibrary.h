// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnhancedInputBinderFunctionLibrary.generated.h"

class UEnhancedInputLocalPlayerSubsystem;

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UEnhancedInputBinderFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "EnhancedInputBinderFunctionLibrary")
    static APlayerController* GetPlayerController(AActor* Owner);

    UFUNCTION(BlueprintCallable, Category = "EnhancedInputBinderFunctionLibrary")
    static APawn* GetPawn(AActor* Owner);

    UFUNCTION(BlueprintCallable, Category = "EnhancedInputBinderFunctionLibrary")
    static UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem(AActor* Owner);
};
