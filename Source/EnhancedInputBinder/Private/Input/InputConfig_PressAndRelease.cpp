// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_PressAndRelease.h"

UInputConfig_PressAndRelease::UInputConfig_PressAndRelease()
{
    TriggerEvents.Empty(2);
    TriggerEvents.Emplace(ETriggerEvent::Started);
    TriggerEvents.Emplace(ETriggerEvent::Completed);
}
