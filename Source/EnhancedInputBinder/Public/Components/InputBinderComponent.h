// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InputMappingContextData.h"
#include "InputBinderComponent.generated.h"

class UInputConfig;
class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(meta = (BlueprintSpawnableComponent))
class ENHANCEDINPUTBINDER_API UInputBinderComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<FInputMappingContextData> InputMappingContextDataList;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UInputConfig>> InputConfigs;

    UPROPERTY(VisibleInstanceOnly, Category = "State")
    TArray<uint32> InputBindingHandles;

public:
    UFUNCTION(BlueprintCallable)
    virtual void BindEnhancedInput();

    UFUNCTION(BlueprintCallable)
    virtual void UnBindEnhancedInput();

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsPawn() const { return GetOwner()->GetClass()->IsChildOf(APawn::StaticClass()); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsPlayerController() const { return GetOwner()->GetClass()->IsChildOf(APlayerController::StaticClass()); }

    UFUNCTION(BlueprintPure)
    APawn* GetOwningPawn() const;

    UFUNCTION(BlueprintPure)
    APlayerController* GetOwningPlayer() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputComponent* GetEnhancedInputComponent() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;

    UFUNCTION(BlueprintCallable)
    virtual void BindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void UnBindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void AddMappingContexts();

    UFUNCTION(BlueprintCallable)
    virtual void RemoveMappingContexts();
};
