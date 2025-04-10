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
    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<FInputMappingContextData> InputMappingContextDataList;

    UPROPERTY(EditAnywhere, Category = "Config")
    TArray<TObjectPtr<UInputConfig>> InputConfigs;

    UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
    TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

    UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
    TArray<uint32> InputBindingHandles;

    UPROPERTY(VisibleInstanceOnly, Transient, Category = "State")
    bool bBound;

public:
    virtual void BeginPlay() override;

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

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsBound() const { return EnhancedInputComponent != nullptr; }

    UFUNCTION(BlueprintCallable)
    virtual void BindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void UnBindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void AddMappingContexts();

    UFUNCTION(BlueprintCallable)
    virtual void RemoveMappingContexts();
};
