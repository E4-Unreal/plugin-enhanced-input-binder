// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InputBinderComponent.h"

#include "EnhancedInputBinderFunctionLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Input/InputConfigBase.h"
#include "Logging.h"
#include "Input/InputConfigSetting.h"

void UInputBinderComponent::BeginPlay()
{
    Super::BeginPlay();

    FindEnhancedInputComponent();

    // Bind Event
    if (APawn* OwningPawn = UEnhancedInputBinderFunctionLibrary::GetPawn(GetOwner()))
    {
        OwningPawn->ReceiveRestartedDelegate.AddDynamic(this, &ThisClass::OnOwningPawnRestarted);
    }
}

void UInputBinderComponent::AddInputMappingContext(UInputMappingContext* InputMappingContext, int32 Priority)
{
    if (!InputMappingContext) return;

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        if (!Subsystem->HasMappingContext(InputMappingContext))
        {
            Subsystem->AddMappingContext(InputMappingContext, Priority);
            LOG_ACTOR_COMPONENT(Log, TEXT("Add MappingContext: %s"), *InputMappingContext->GetName())
        }
    }
}

void UInputBinderComponent::RemoveInputMappingContext(UInputMappingContext* InputMappingContext)
{
    if (!InputMappingContext) return;

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputLocalPlayerSubsystem())
    {
        if (Subsystem->HasMappingContext(InputMappingContext))
        {
            Subsystem->RemoveMappingContext(InputMappingContext);
            LOG_ACTOR_COMPONENT(Log, TEXT("Remove MappingContext: %s"), *InputMappingContext->GetName())
        }
    }
}

void UInputBinderComponent::BindInputConfig(UInputConfigBase* InputConfig)
{
    if (bool bCanBind = InputConfig && !InputBindingHandleMap.Contains(InputConfig); !bCanBind) return;

    InputBindingHandleMap.Emplace(InputConfig, InputConfig->BindEnhancedInput(GetEnhancedInputComponent()));
    LOG_ACTOR_COMPONENT(Log, TEXT("Bind InputConfig: %s"), *InputConfig->GetName())


}

void UInputBinderComponent::UnBindInputConfig(UInputConfigBase* InputConfig)
{
    if (bool bCanUnBind = InputConfig && InputBindingHandleMap.Contains(InputConfig); !bCanUnBind) return;

    for (uint32 Handle : InputBindingHandleMap[InputConfig].Handles)
    {
        GetEnhancedInputComponent()->RemoveActionBindingForHandle(Handle);
    }
    InputBindingHandleMap.Remove(InputConfig);
    LOG_ACTOR_COMPONENT(Log, TEXT("UnBind InputConfig: %s"), *InputConfig->GetName())
}

void UInputBinderComponent::BindInputConfigSetting(UInputConfigSetting* InputConfigSetting)
{
    if (!InputConfigSetting) return;

    AddInputMappingContext(InputConfigSetting->GetInputMappingContext(), InputConfigSetting->GetPriority());
    for (auto InputConfig : InputConfigSetting->GetInputConfigs())
    {
        BindInputConfig(InputConfig);
    }
}

void UInputBinderComponent::UnBindInputConfigSetting(UInputConfigSetting* InputConfigSetting)
{
    if (!InputConfigSetting) return;

    RemoveInputMappingContext(InputConfigSetting->GetInputMappingContext());
    for (auto InputConfig : InputConfigSetting->GetInputConfigs())
    {
        UnBindInputConfig(InputConfig);
    }
}

void UInputBinderComponent::BindEnhancedInput()
{
    // Bind InputConfigSettings
    for (const auto& InputConfigSetting : InputConfigSettings)
    {
        BindInputConfigSetting(InputConfigSetting);
    }

    // Add Additional InputMappingContexts
    for (const auto& [InputMappingContext, Priority] : AdditionalInputMappingContexts)
    {
        AddInputMappingContext(InputMappingContext, Priority);
    }

    // Bind Additional InputConfigs
    for (const auto& InputConfig : AdditionalInputConfigs)
    {
        BindInputConfig(InputConfig);
    }
}

void UInputBinderComponent::UnBindEnhancedInput()
{
    // UnBind InputConfigSettings
    for (auto InputConfigSetting : InputConfigSettings)
    {
        UnBindInputConfigSetting(InputConfigSetting);
    }

    // Remove Additional InputMappingContexts
    for (const auto& [InputMappingContext, Priority] : AdditionalInputMappingContexts)
    {
        RemoveInputMappingContext(InputMappingContext);
    }

    // UnBind Additional InputConfigs
    for (const auto& InputConfig : AdditionalInputConfigs)
    {
        UnBindInputConfig(InputConfig);
    }
}

void UInputBinderComponent::SetEnhancedInputComponent(UEnhancedInputComponent* NewEnhancedInputComponent)
{
    if (EnhancedInputComponent == NewEnhancedInputComponent) return;

    UnBindEnhancedInput();

    EnhancedInputComponent = NewEnhancedInputComponent;
    PlayerController = UEnhancedInputBinderFunctionLibrary::GetPlayerController(GetOwner());
    EnhancedInputLocalPlayerSubsystem = UEnhancedInputBinderFunctionLibrary::GetEnhancedInputLocalPlayerSubsystem(GetOwner());

    BindEnhancedInput();
}

void UInputBinderComponent::FindEnhancedInputComponent()
{
    if (GetEnhancedInputComponent()) return;

    if (APawn* OwningPawn = UEnhancedInputBinderFunctionLibrary::GetPawn(GetOwner()))
    {
        SetEnhancedInputComponent(Cast<UEnhancedInputComponent>(OwningPawn->InputComponent));
    }
    else if (APlayerController* OwningPlayerController = UEnhancedInputBinderFunctionLibrary::GetPlayerController(GetOwner()))
    {
        SetEnhancedInputComponent(Cast<UEnhancedInputComponent>(OwningPlayerController->InputComponent));
    }
    else
    {
        checkf(false, TEXT("%s::%s's owner must be Pawn or PlayerController!"), *GetOwner()->GetName(), *GetName());
    }
}

void UInputBinderComponent::OnOwningPawnRestarted(APawn* OwningPawn)
{
    SetEnhancedInputComponent(Cast<UEnhancedInputComponent>(OwningPawn->InputComponent));
}
