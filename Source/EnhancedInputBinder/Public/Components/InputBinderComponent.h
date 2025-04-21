// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InputBindingHandleList.h"
#include "InputBinderComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UInputConfigBase;
class UInputConfigSetting;

UCLASS(meta = (BlueprintSpawnableComponent))
class ENHANCEDINPUTBINDER_API UInputBinderComponent : public UActorComponent
{
    GENERATED_BODY()

    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
    TWeakObjectPtr<APlayerController> PlayerController;
    TWeakObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TObjectPtr<UInputConfigSetting>> InputConfigSettings;

    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TMap<TObjectPtr<UInputConfigBase>, FInputBindingHandleList> InputBindingHandleMap;

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void AddInputMappingContext(UInputMappingContext* InputMappingContext, int32 Priority);

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void RemoveInputMappingContext(UInputMappingContext* InputMappingContext);

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void BindInputConfig(UInputConfigBase* InputConfig);

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void UnBindInputConfig(UInputConfigBase* InputConfig);

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void BindInputConfigSetting(UInputConfigSetting* InputConfigSetting);

    UFUNCTION(BlueprintCallable, Category = "InputBinderComponent")
    virtual void UnBindInputConfigSetting(UInputConfigSetting* InputConfigSetting);

protected:
    virtual void FindEnhancedInputComponent();

    virtual void BindEnhancedInput();
    virtual void UnBindEnhancedInput();

    UFUNCTION()
    virtual void OnOwningPawnRestarted(APawn* OwningPawn);

public:
    void SetEnhancedInputComponent(UEnhancedInputComponent* NewEnhancedInputComponent);

protected:
    FORCEINLINE UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent.Get(); }
    FORCEINLINE APlayerController* GetPlayerController() const { return PlayerController.Get(); }
    FORCEINLINE UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const { return EnhancedInputLocalPlayerSubsystem.Get(); }
};
