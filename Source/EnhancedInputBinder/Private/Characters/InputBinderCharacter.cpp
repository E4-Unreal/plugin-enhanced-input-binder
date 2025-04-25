// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/InputBinderCharacter.h"

#include "Components/InputBinderComponent.h"

const FName AInputBinderCharacter::InputBinderName(TEXT("InputBinder"));

AInputBinderCharacter::AInputBinderCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);
}
