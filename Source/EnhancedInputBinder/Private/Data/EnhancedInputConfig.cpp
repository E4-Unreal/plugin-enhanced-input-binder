// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/EnhancedInputConfig.h"

#include "EnhancedInputComponent.h"

TArray<uint32> UEnhancedInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent != nullptr ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

APawn* UEnhancedInputConfig::GetOwningPlayerPawn(UEnhancedInputComponent* EnhancedInputComponent)
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

APlayerController* UEnhancedInputConfig::GetOwningPlayer(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APawn* OwningPawn = GetOwningPlayerPawn(EnhancedInputComponent))
    {
        return Cast<APlayerController>(OwningPawn->GetController());
    }

    return nullptr;
}
