// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnhancedInputBinderComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Data/EnhancedInputConfig.h"
#include "Logging.h"

#define LOG_OWNER_ERROR LOG_ACTOR_COMPONENT(Error, TEXT("Owner should be PlayerController or Pawn!"))

APawn* UEnhancedInputBinderComponent::GetOwningPawn() const
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

APlayerController* UEnhancedInputBinderComponent::GetOwningPlayer() const
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

UEnhancedInputComponent* UEnhancedInputBinderComponent::GetEnhancedInputComponent() const
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

UEnhancedInputLocalPlayerSubsystem* UEnhancedInputBinderComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    if (APlayerController* PlayerController = GetOwningPlayer())
    {
        return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    }

    return nullptr;
}

void UEnhancedInputBinderComponent::BindEnhancedInput()
{
    BindInputConfigs();

    AddMappingContexts();
}

void UEnhancedInputBinderComponent::UnBindEnhancedInput()
{
    UnBindInputConfigs();

    RemoveMappingContexts();
}

void UEnhancedInputBinderComponent::BindInputConfigs()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
    {
        for (const auto& InputConfig : InputConfigs)
        {
            if(InputConfig)
            {
                InputBindingHandles.Append(InputConfig->BindEnhancedInput(EnhancedInputComponent));
            }
        }
    }
}

void UEnhancedInputBinderComponent::UnBindInputConfigs()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetEnhancedInputComponent())
    {
        for (const auto& InputBindingHandle : InputBindingHandles)
        {
            EnhancedInputComponent->RemoveActionBindingForHandle(InputBindingHandle);
        }

        InputBindingHandles.Reset();
    }
}

void UEnhancedInputBinderComponent::AddMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (const auto& [InputMappingContext, Priority] : InputMappingContextDataList)
        {
            if (!Subsystem->HasMappingContext(InputMappingContext))
            {
                Subsystem->AddMappingContext(InputMappingContext, Priority);
            }
        }
    }
}

void UEnhancedInputBinderComponent::RemoveMappingContexts()
{
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        for (const auto& [InputMappingContext, Priority] : InputMappingContextDataList)
        {
            if (Subsystem->HasMappingContext(InputMappingContext))
            {
                Subsystem->RemoveMappingContext(InputMappingContext);
            }
        }
    }
}
