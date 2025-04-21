// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

TArray<UInputAction*> UInputConfig::GetInputActions() const
{
    TArray<UInputAction*> InputActions = { InputAction };
    return InputActions;
}
