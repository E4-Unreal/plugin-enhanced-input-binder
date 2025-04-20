// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputBinderComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/InputConfig.h"
#include "Logging.h"

#define LOG_OWNER_ERROR LOG_ACTOR_COMPONENT(Error, TEXT("Owner should be PlayerController or Pawn!"))

void UInputBinderComponent::BeginPlay()
{
    Super::BeginPlay();

    BindEnhancedInput();
}

APawn* UInputBinderComponent::GetOwningPawn() const
{
    if (IsPawn())
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        return OwningPawn;
    }
    else if (IsPlayerController())
    {
        APlayerController* OwningPlayer = Cast<APlayerController>(GetOwner());
        return OwningPlayer->GetPawn();
    }
    else
    {
        LOG_OWNER_ERROR

        return nullptr;
    }
}

APlayerController* UInputBinderComponent::GetOwningPlayer() const
{
    if (IsPawn())
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        return Cast<APlayerController>(OwningPawn->GetController());
    }
    else if (IsPlayerController())
    {
        APlayerController* OwningPlayer = Cast<APlayerController>(GetOwner());
        return OwningPlayer;
    }
    else
    {
        LOG_OWNER_ERROR

        return nullptr;
    }
}

UEnhancedInputComponent* UInputBinderComponent::GetEnhancedInputComponent() const
{
    if (IsPawn())
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        return Cast<UEnhancedInputComponent>(OwningPawn->InputComponent);
    }
    else if (IsPlayerController())
    {
        APlayerController* OwningPlayer = Cast<APlayerController>(GetOwner());
        return Cast<UEnhancedInputComponent>(OwningPlayer->InputComponent);
    }
    else
    {
        LOG_OWNER_ERROR

        return nullptr;
    }
}

UEnhancedInputLocalPlayerSubsystem* UInputBinderComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    if (APlayerController* PlayerController = GetOwningPlayer())
    {
        return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    }

    return nullptr;
}

void UInputBinderComponent::BindEnhancedInput()
{
    if (IsBound()) return;
    EnhancedInputComponent = GetEnhancedInputComponent();

    BindInputConfigs();

    AddMappingContexts();

    bBound = true;
}

void UInputBinderComponent::UnBindEnhancedInput()
{
    if (!IsBound()) return;
    EnhancedInputComponent = nullptr;

    UnBindInputConfigs();

    RemoveMappingContexts();

    bBound = false;
}

void UInputBinderComponent::BindInputConfigs()
{
    if (!EnhancedInputComponent) return;

    // Bind InputConfig
    for (const auto& InputConfig : InputConfigs)
    {
        // Add InputBinding Handles
        InputBindingHandles.Append(InputConfig->BindEnhancedInput(EnhancedInputComponent));
    }
}

void UInputBinderComponent::UnBindInputConfigs()
{
    if (!EnhancedInputComponent) return;

    // Remove InputBinding For Handles
    for (const auto& InputBindingHandle : InputBindingHandles)
    {
        EnhancedInputComponent->RemoveActionBindingForHandle(InputBindingHandle);
    }

    InputBindingHandles.Reset();

    // UnBind InputConfig
    for (const auto& InputConfig : InputConfigs)
    {
        InputConfig->UnBindEnhancedInput(EnhancedInputComponent);
    }
}

void UInputBinderComponent::AddMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (const auto& InputMappingContext : InputMappingContexts)
        {
            if (!Subsystem->HasMappingContext(InputMappingContext))
            {
                Subsystem->AddMappingContext(InputMappingContext, Priority);
            }
        }
    }
}

void UInputBinderComponent::RemoveMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (const auto& InputMappingContext : InputMappingContexts)
        {
            if (Subsystem->HasMappingContext(InputMappingContext))
            {
                Subsystem->RemoveMappingContext(InputMappingContext);
            }
        }
    }
}
