// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputBinderComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Input/InputConfigBase.h"
#include "Logging.h"

void UInputBinderComponent::BeginPlay()
{
    Super::BeginPlay();

    FindEnhancedInputComponent();
}

void UInputBinderComponent::BindEnhancedInput()
{
    if (bool bCanBind = !bBound && GetEnhancedInputComponent(); !bCanBind) return;
    bBound = true;

    AddMappingContexts();
    BindInputConfigs();
}

void UInputBinderComponent::UnBindEnhancedInput()
{
    if (!bBound) return;
    bBound = false;

    if (GetEnhancedInputComponent())
    {
        UnBindInputConfigs();
        RemoveMappingContexts();
    }
    else
    {
        InputBindingHandles.Reset();
    }
}

void UInputBinderComponent::SetEnhancedInputComponent(UEnhancedInputComponent* NewEnhancedInputComponent)
{
    if (EnhancedInputComponent == NewEnhancedInputComponent) return;

    UnBindEnhancedInput();
    EnhancedInputComponent = NewEnhancedInputComponent;
    BindEnhancedInput();
}

void UInputBinderComponent::FindEnhancedInputComponent()
{
    if (GetEnhancedInputComponent()) return;

    if (APawn* OwningPawn = GetOwningPawn())
    {
        OnOwningPawnRestarted(OwningPawn);
        OwningPawn->ReceiveRestartedDelegate.AddDynamic(this, &ThisClass::OnOwningPawnRestarted);
    }
    else if (APlayerController* OwningPlayerController = GetOwningPlayerController())
    {
        SetEnhancedInputComponent(Cast<UEnhancedInputComponent>(OwningPlayerController->InputComponent));
    }
    else
    {
        checkf(false, TEXT("%s::%s's owner must be Pawn or PlayerController!"), *GetOwner()->GetName(), *GetName());
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
                LOG_ACTOR_COMPONENT(Log, TEXT("Add MappingContext: %s"), *InputMappingContext->GetName())
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
                LOG_ACTOR_COMPONENT(Log, TEXT("Remove MappingContext: %s"), *InputMappingContext->GetName())
                Subsystem->RemoveMappingContext(InputMappingContext);
            }
        }
    }
}

void UInputBinderComponent::BindInputConfigs()
{
    // Bind InputConfig
    for (const auto& InputConfig : InputConfigs)
    {
        // Add InputBinding Handles
        LOG_ACTOR_COMPONENT(Log, TEXT("Bind InputConfig: %s"), *InputConfig->GetName())
        InputBindingHandles.Append(InputConfig->BindEnhancedInput(GetEnhancedInputComponent()));
    }
}

void UInputBinderComponent::UnBindInputConfigs()
{
    // Remove InputBinding For Handles
    for (const auto& InputBindingHandle : InputBindingHandles)
    {
        GetEnhancedInputComponent()->RemoveActionBindingForHandle(InputBindingHandle);
    }

    InputBindingHandles.Reset();

    // UnBind InputConfig
    for (const auto& InputConfig : InputConfigs)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("UnBind InputConfig: %s"), *InputConfig->GetName())
        InputConfig->UnBindEnhancedInput(GetEnhancedInputComponent());
    }
}

APawn* UInputBinderComponent::GetOwningPawn() const
{
    auto OwningPawn = Cast<APawn>(GetOwner());
    if (!OwningPawn)
    {
        if (auto OwningPlayerController = Cast<APlayerController>(GetOwner()))
        {
            OwningPawn = OwningPlayerController->GetPawn();
        }
    }

    return OwningPawn;
}

APlayerController* UInputBinderComponent::GetOwningPlayerController() const
{
    auto OwningPlayerController = Cast<APlayerController>(GetOwner());
    if (!OwningPlayerController)
    {
        if (auto OwningPawn = Cast<APawn>(GetOwner()))
        {
            OwningPlayerController = Cast<APlayerController>(OwningPawn->Controller);
        }
    }

    return OwningPlayerController;
}

UEnhancedInputLocalPlayerSubsystem* UInputBinderComponent::GetEnhancedInputLocalPlayerSubsystem() const
{
    APlayerController* PlayerController = GetOwningPlayerController();
    return PlayerController ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) : nullptr;
}

void UInputBinderComponent::OnOwningPawnRestarted(APawn* OwningPawn)
{
    SetEnhancedInputComponent(Cast<UEnhancedInputComponent>(OwningPawn->InputComponent));
}
