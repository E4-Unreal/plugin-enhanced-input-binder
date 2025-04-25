// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputBinderPawn.generated.h"

class UInputBinderComponent;

UCLASS()
class ENHANCEDINPUTBINDER_API AInputBinderPawn : public APawn
{
    GENERATED_BODY()

protected:
    static const FName InputBinderName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputBinderComponent> InputBinder;

public:
    AInputBinderPawn(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
};
