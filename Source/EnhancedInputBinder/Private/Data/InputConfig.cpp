// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputConfig.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

TArray<uint32> UInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent != nullptr ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
}

APawn* UInputConfig::GetOwningPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (auto OwningActor = EnhancedInputComponent->GetOwner())
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
        if (auto OwningActor = EnhancedInputComponent->GetOwner())
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
    if (auto OwningPawn = GetOwningPawn(EnhancedInputComponent))
    {
        return Cast<APlayerController>(OwningPawn->GetController());
    }

    return nullptr;
}
