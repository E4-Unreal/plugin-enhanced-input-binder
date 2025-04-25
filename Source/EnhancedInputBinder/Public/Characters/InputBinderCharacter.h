// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputBinderCharacter.generated.h"

class UInputBinderComponent;

UCLASS()
class ENHANCEDINPUTBINDER_API AInputBinderCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    static const FName InputBinderName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputBinderComponent> InputBinder;

public:
    AInputBinderCharacter(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
};
