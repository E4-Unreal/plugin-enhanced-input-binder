// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputBinderComponent.generated.h"

class UInputMappingContext;
class UInputConfigBase;
class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(meta = (BlueprintSpawnableComponent))
class ENHANCEDINPUTBINDER_API UInputBinderComponent : public UActorComponent
{
    GENERATED_BODY()

    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    int32 Priority;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TSet<TObjectPtr<UInputMappingContext>> InputMappingContexts;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TSet<TObjectPtr<UInputConfigBase>> InputConfigs;

    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TArray<uint32> InputBindingHandles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    bool bBound = false;

public:
    virtual void BeginPlay() override;
    
    virtual void BindEnhancedInput();
    virtual void UnBindEnhancedInput();

    void SetEnhancedInputComponent(UEnhancedInputComponent* NewEnhancedInputComponent);

protected:
    virtual void FindEnhancedInputComponent();

    virtual void AddMappingContexts();
    virtual void RemoveMappingContexts();

    virtual void BindInputConfigs();
    virtual void UnBindInputConfigs();

    FORCEINLINE UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent.Get(); }

    APawn* GetOwningPawn() const;
    APlayerController* GetOwningPlayerController() const;
    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;

    UFUNCTION()
    virtual void OnOwningPawnRestarted(APawn* OwningPawn);
};
