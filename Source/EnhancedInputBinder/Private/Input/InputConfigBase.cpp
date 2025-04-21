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
    return EnhancedInputComponent && IsValid() ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

void UInputConfigBase::UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent && IsValid()) OnUnBindEnhancedInput(EnhancedInputComponent);
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
            BindInputActions(EnhancedInputComponent, TriggerEvent, FInputActionDelegate::CreateUObject(this, &ThisClass::OnTriggered), InputBindingHandles);
            break;
        case ETriggerEvent::Started:
            BindInputActions(EnhancedInputComponent, TriggerEvent, FInputActionDelegate::CreateUObject(this, &ThisClass::OnStarted), InputBindingHandles);
            break;
        case ETriggerEvent::Ongoing:
            BindInputActions(EnhancedInputComponent, TriggerEvent, FInputActionDelegate::CreateUObject(this, &ThisClass::OnOngoing), InputBindingHandles);
            break;
        case ETriggerEvent::Canceled:
            BindInputActions(EnhancedInputComponent, TriggerEvent, FInputActionDelegate::CreateUObject(this, &ThisClass::OnCanceled), InputBindingHandles);
            break;
        case ETriggerEvent::Completed:
            BindInputActions(EnhancedInputComponent, TriggerEvent, FInputActionDelegate::CreateUObject(this, &ThisClass::OnCompleted), InputBindingHandles);
            break;
        }
    }

    return InputBindingHandles;
}

void UInputConfigBase::OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{

}

void UInputConfigBase::BindInputActions(UEnhancedInputComponent* EnhancedInputComponent, ETriggerEvent TriggerEvent,
    const FInputActionDelegate& InputActionDelegate, TArray<uint32>& InputBindingHandles) const
{
    for (auto LocalInputAction : GetInputActions())
    {
        auto& InputActionBinding = EnhancedInputComponent->BindActionInstanceLambda(
            LocalInputAction,
            TriggerEvent,
            [EnhancedInputComponent, InputActionDelegate](const FInputActionInstance& ActionInstance)
            {
                InputActionDelegate.Execute(EnhancedInputComponent, ActionInstance);
            });

        InputBindingHandles.Emplace(InputActionBinding.GetHandle());
    }
}

void UInputConfigBase::OnTriggered_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)
{
    if (bEnableLog)
    {
        LOG(Log, TEXT("%s triggered by %s"), *InputActionInstance.GetSourceAction()->GetName(), *GetPlayerController(EnhancedInputComponent)->GetName())
    }
}

void UInputConfigBase::OnStarted_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)
{
    if (bEnableLog)
    {
        LOG(Log, TEXT("%s started by %s"), *InputActionInstance.GetSourceAction()->GetName(), *GetPlayerController(EnhancedInputComponent)->GetName())
    }
}

void UInputConfigBase::OnOngoing_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)
{
    if (bEnableLog)
    {
        LOG(Log, TEXT("%s ongoing by %s"), *InputActionInstance.GetSourceAction()->GetName(), *GetPlayerController(EnhancedInputComponent)->GetName())
    }
}

void UInputConfigBase::OnCanceled_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)
{
    if (bEnableLog)
    {
        LOG(Log, TEXT("%s canceled by %s"), *InputActionInstance.GetSourceAction()->GetName(), *GetPlayerController(EnhancedInputComponent)->GetName())
    }
}

void UInputConfigBase::OnCompleted_Implementation(UEnhancedInputComponent* EnhancedInputComponent, const FInputActionInstance& InputActionInstance)
{
    if (bEnableLog)
    {
        LOG(Log, TEXT("%s completed by %s"), *InputActionInstance.GetSourceAction()->GetName(), *GetPlayerController(EnhancedInputComponent)->GetName())
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
