// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputConfig_ToggleWidget.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

TArray<uint32> UInputConfig_ToggleWidget::OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    TArray<uint32> InputBindingHandles;
    APlayerController* PlayerController = GetOwningPlayer(EnhancedInputComponent);
    if (PlayerController == nullptr) return InputBindingHandles;

    for (const auto& [InputActionData, WidgetClass] : InputActionMap)
    {
        if (InputActionData.IsNotValid() || WidgetClass == nullptr) continue;

        auto Widget = CreateWidget(PlayerController, WidgetClass);

        FEnhancedInputActionEventBinding& Binding = EnhancedInputComponent->BindAction(
                InputActionData.InputAction,
                InputActionData.TriggerEvent,
                this,
                &ThisClass::ToggleWidget,
                Widget
                );

        InputBindingHandles.Emplace(Binding.GetHandle());
    }

    return InputBindingHandles;
}

void UInputConfig_ToggleWidget::ToggleWidget(UUserWidget* Widget)
{
    if (Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
    }
    else
    {
        Widget->AddToViewport();
    }
}
