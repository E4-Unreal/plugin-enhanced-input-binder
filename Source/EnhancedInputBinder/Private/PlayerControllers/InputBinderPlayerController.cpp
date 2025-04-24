// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/InputBinderPlayerController.h"

#include "Components/InputBinderComponent.h"

const FName AInputBinderPlayerController::InputBinderName(TEXT("InputBinder"));

AInputBinderPlayerController::AInputBinderPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);
}
