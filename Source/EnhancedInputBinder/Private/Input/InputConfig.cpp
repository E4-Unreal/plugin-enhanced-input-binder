// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Logging.h"

UInputConfig::UInputConfig()
{
    TriggerEvents.Emplace(ETriggerEvent::Triggered);
}

TArray<uint32> UInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent && InputAction ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

void UInputConfig::UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent && InputAction) OnUnBindEnhancedInput(EnhancedInputComponent);
}

TArray<uint32> UInputConfig::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;

    for (auto TriggerEvent : TriggerEvents)
    {
        switch (TriggerEvent)
        {
        case ETriggerEvent::None:
            break;
        case ETriggerEvent::Triggered:
            InputBindingHandles.Emplace(BindTriggeredEvent(EnhancedInputComponent));
            break;
        case ETriggerEvent::Started:
            InputBindingHandles.Emplace(BindStartedEvent(EnhancedInputComponent));
            break;
        case ETriggerEvent::Ongoing:
            InputBindingHandles.Emplace(BindOngoingEvent(EnhancedInputComponent));
            break;
        case ETriggerEvent::Canceled:
            InputBindingHandles.Emplace(BindCanceledEvent(EnhancedInputComponent));
            break;
        case ETriggerEvent::Completed:
            InputBindingHandles.Emplace(BindCompletedEvent(EnhancedInputComponent));
            break;
        }
    }

    return InputBindingHandles;
}

void UInputConfig::OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{

}

uint32 UInputConfig::BindTriggeredEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetOwningPawn(EnhancedInputComponent);
    auto PlayerController = GetOwningPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Triggered,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnTriggered(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfig::BindStartedEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetOwningPawn(EnhancedInputComponent);
    auto PlayerController = GetOwningPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Started,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnStarted(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfig::BindOngoingEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetOwningPawn(EnhancedInputComponent);
    auto PlayerController = GetOwningPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Ongoing,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnOngoing(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfig::BindCanceledEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetOwningPawn(EnhancedInputComponent);
    auto PlayerController = GetOwningPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Canceled,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnCanceled(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfig::BindCompletedEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetOwningPawn(EnhancedInputComponent);
    auto PlayerController = GetOwningPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Completed,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnCompleted(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

void UInputConfig::OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s triggered by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfig::OnStarted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s started by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfig::OnOngoing_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s ongoing by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfig::OnCanceled_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s canceled by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfig::OnCompleted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s completed by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

APawn* UInputConfig::GetOwningPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    return Cast<APawn>(EnhancedInputComponent->GetOwner());
}

APlayerController* UInputConfig::GetOwningPlayerController(UEnhancedInputComponent* EnhancedInputComponent)
{
    APlayerController* OwningPlayerController = Cast<APlayerController>(EnhancedInputComponent->GetOwner());
    if (OwningPlayerController) Cast<APlayerController>(GetOwningPawn(EnhancedInputComponent)->GetController());

    return OwningPlayerController;
}

UEnhancedInputLocalPlayerSubsystem* UInputConfig::GetEnhancedInputLocalPlayerSubsystem(
    UEnhancedInputComponent* EnhancedInputComponent)
{
    return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetOwningPlayerController(EnhancedInputComponent)->GetLocalPlayer());
}
