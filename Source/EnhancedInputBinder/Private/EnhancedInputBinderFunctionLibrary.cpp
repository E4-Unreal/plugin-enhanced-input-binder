// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputBinderFunctionLibrary.h"

APlayerController* UEnhancedInputBinderFunctionLibrary::GetPlayerController(AActor* Owner)
{
    if (!Owner) return nullptr;

    auto OwningPlayerController = Cast<APlayerController>(Owner);
    if (!OwningPlayerController)
    {
        if (auto OwningPawn = Cast<APawn>(Owner))
        {
            OwningPlayerController = Cast<APlayerController>(OwningPawn->Controller);
        }
    }

    return OwningPlayerController;
}

APawn* UEnhancedInputBinderFunctionLibrary::GetPawn(AActor* Owner)
{
    if (!Owner) return nullptr;

    auto OwningPawn = Cast<APawn>(Owner);
    if (!OwningPawn)
    {
        if (auto OwningPlayerController = Cast<APlayerController>(Owner))
        {
            OwningPawn = OwningPlayerController->GetPawn();
        }
    }

    return OwningPawn;
}

UEnhancedInputLocalPlayerSubsystem* UEnhancedInputBinderFunctionLibrary::GetEnhancedInputLocalPlayerSubsystem(AActor* Owner)
{
    if (!Owner) return nullptr;

    APlayerController* PlayerController = GetPlayerController(Owner);
    return PlayerController ? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()) : nullptr;
}
