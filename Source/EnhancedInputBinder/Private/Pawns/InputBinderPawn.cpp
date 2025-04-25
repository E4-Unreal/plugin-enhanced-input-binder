// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/InputBinderPawn.h"

#include "Components/InputBinderComponent.h"

const FName AInputBinderPawn::InputBinderName(TEXT("InputBinder"));

AInputBinderPawn::AInputBinderPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InputBinder = CreateDefaultSubobject<UInputBinderComponent>(InputBinderName);
}
