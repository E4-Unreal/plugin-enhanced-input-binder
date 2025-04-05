// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputConfig.h"

#include "EnhancedInputComponent.h"

TArray<uint32> UInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent != nullptr ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

APawn* UInputConfig::GetOwningPlayerPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (AActor* OwningActor = EnhancedInputComponent->GetOwner())
        {
            if (APawn* OwningPawn = Cast<APawn>(OwningActor))
            {
                return OwningPawn;
            }
        }
    }

    return nullptr;
}

APlayerController* UInputConfig::GetOwningPlayer(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APawn* OwningPawn = GetOwningPlayerPawn(EnhancedInputComponent))
    {
        return Cast<APlayerController>(OwningPawn->GetController());
    }

    return nullptr;
}
