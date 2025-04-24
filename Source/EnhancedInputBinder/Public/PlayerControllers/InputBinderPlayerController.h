// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputBinderPlayerController.generated.h"

class UInputBinderComponent;
/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API AInputBinderPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    static const FName InputBinderName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputBinderComponent> InputBinder;

public:
    AInputBinderPlayerController(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
};
