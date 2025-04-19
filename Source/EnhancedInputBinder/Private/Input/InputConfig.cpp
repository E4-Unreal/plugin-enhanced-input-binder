// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

TArray<uint32> UInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent != nullptr ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

void UInputConfig::UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    OnUnBindEnhancedInput(EnhancedInputComponent);
}

APawn* UInputConfig::GetOwningPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (AActor* OwningActor = EnhancedInputComponent->GetOwner())
        {
            if (auto OwningPawn = Cast<APawn>(OwningActor))
            {
                return OwningPawn;
            }
        }
    }

    return nullptr;
}

ACharacter* UInputConfig::GetOwningCharacter(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (AActor* OwningActor = EnhancedInputComponent->GetOwner())
        {
            if (auto OwningCharacter = Cast<ACharacter>(OwningActor))
            {
                return OwningCharacter;
            }
        }
    }

        return nullptr;
}

APlayerController* UInputConfig::GetOwningPlayerController(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APawn* OwningPawn = GetOwningPawn(EnhancedInputComponent))
    {
        return Cast<APlayerController>(OwningPawn->GetController());
    }

    return nullptr;
}

UEnhancedInputLocalPlayerSubsystem* UInputConfig::GetEnhancedInputLocalPlayerSubsystem(
    UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APlayerController* PlayerController = GetOwningPlayerController(EnhancedInputComponent))
    {
        return ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    }

    return nullptr;
}

void UInputConfig::OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
}
