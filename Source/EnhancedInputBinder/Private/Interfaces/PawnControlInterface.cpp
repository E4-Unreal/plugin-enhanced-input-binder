// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PawnControlInterface.h"

#include "InputActionValue.h"
#include "Logging.h"


// Add default functionality here for any IPawnControlInterface functions that are not pure virtual.
void IPawnControlInterface::Move_Implementation(const FInputActionValue& ActionValue)
{
    LOG_TODO_INTERFACE
}

void IPawnControlInterface::Look_Implementation(const FInputActionValue& ActionValue)
{
    LOG_TODO_INTERFACE
}
