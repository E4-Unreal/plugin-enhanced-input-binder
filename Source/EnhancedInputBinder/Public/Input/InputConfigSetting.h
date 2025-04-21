// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputConfigSetting.generated.h"

class UInputMappingContext;
class UInputConfigBase;

/**
 *
 */
UCLASS()
class ENHANCEDINPUTBINDER_API UInputConfigSetting : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    int32 Priority;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    TArray<TObjectPtr<UInputConfigBase>> InputConfigs;

public:
    FORCEINLINE int32 GetPriority() const { return Priority; }
    FORCEINLINE UInputMappingContext* GetInputMappingContext() const { return InputMappingContext.Get(); }
    FORCEINLINE const TArray<TObjectPtr<UInputConfigBase>>& GetInputConfigs() const { return InputConfigs; }
};
