// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfigBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Logging.h"

UInputConfigBase::UInputConfigBase()
{
    TriggerEvents.Emplace(ETriggerEvent::Triggered);
}

TArray<uint32> UInputConfigBase::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent && InputAction ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

void UInputConfigBase::UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent && InputAction) OnUnBindEnhancedInput(EnhancedInputComponent);
}

TArray<uint32> UInputConfigBase::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
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

void UInputConfigBase::OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{

}

uint32 UInputConfigBase::BindTriggeredEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetPawn(EnhancedInputComponent);
    auto PlayerController = GetPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Triggered,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnTriggered(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfigBase::BindStartedEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetPawn(EnhancedInputComponent);
    auto PlayerController = GetPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Started,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnStarted(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfigBase::BindOngoingEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetPawn(EnhancedInputComponent);
    auto PlayerController = GetPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Ongoing,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnOngoing(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfigBase::BindCanceledEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetPawn(EnhancedInputComponent);
    auto PlayerController = GetPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Canceled,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnCanceled(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

uint32 UInputConfigBase::BindCompletedEvent(UEnhancedInputComponent* EnhancedInputComponent)
{
    auto Pawn = GetPawn(EnhancedInputComponent);
    auto PlayerController = GetPlayerController(EnhancedInputComponent);

    FEnhancedInputActionEventBinding& InputActionBinding = EnhancedInputComponent->BindActionValueLambda(
        InputAction,
        ETriggerEvent::Completed,
        [Pawn, PlayerController, this](const FInputActionValue& InputActionValue)
        {
            OnCompleted(Pawn, PlayerController, InputActionValue);
        });

    return InputActionBinding.GetHandle();
}

void UInputConfigBase::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent, ETriggerEvent TriggerEvent,
    TFunction<void(UEnhancedInputComponent*, const FInputActionInstance&)> EventFunction,
    TArray<uint32>& InputBindingHandles) const
{
    if (bool bCanBind = EnhancedInputComponent && TriggerEvent != ETriggerEvent::None; !bCanBind) return;

    for (auto InputAction : GetInputActions())
    {
        auto& InputActionBinding = EnhancedInputComponent->BindActionInstanceLambda(
            InputAction,
            TriggerEvent,
            [EnhancedInputComponent, EventFunction](const FInputActionInstance& ActionInstance)
            {
                EventFunction(EnhancedInputComponent, ActionInstance);
            });

        InputBindingHandles.Emplace(InputActionBinding.GetHandle());
    }
}

void UInputConfigBase::OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s triggered by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfigBase::OnStarted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s started by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfigBase::OnOngoing_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s ongoing by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfigBase::OnCanceled_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s canceled by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

void UInputConfigBase::OnCompleted_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue)
{
    if (bEnableLog)
    {
        AActor* Instigator = Pawn;
        if (!Instigator) Instigator = PlayerController;
        LOG(Log, TEXT("%s completed by %s"), *InputAction->GetName(), *Instigator->GetName())
    }
}

APlayerController* UInputConfigBase::GetPlayerController(UEnhancedInputComponent* EnhancedInputComponent)
{
    APlayerController* OwningPlayerController = Cast<APlayerController>(EnhancedInputComponent->GetOwner());
    if (!OwningPlayerController) OwningPlayerController = Cast<APlayerController>(Cast<APawn>(EnhancedInputComponent->GetOwner())->GetController());

    return OwningPlayerController;
}

APawn* UInputConfigBase::GetPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    return GetPlayerController(EnhancedInputComponent)->GetPawn();
}

UEnhancedInputLocalPlayerSubsystem* UInputConfigBase::GetEnhancedInputLocalPlayerSubsystem(
    UEnhancedInputComponent* EnhancedInputComponent)
{
    return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController(EnhancedInputComponent)->GetLocalPlayer());
}
