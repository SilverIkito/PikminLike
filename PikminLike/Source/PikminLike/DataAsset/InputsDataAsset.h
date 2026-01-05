// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include <InputMappingContext.h>
#include "InputsDataAsset.generated.h"

enum EInputEnum;

UCLASS()
class PIKMINLIKE_API UInputsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> IMC;
	UPROPERTY(EditAnywhere) TMap<FName, TObjectPtr<UInputAction>> inputsAction;
	UPROPERTY(EditAnywhere) TEnumAsByte<EInputEnum> state;

public:
	FORCEINLINE TObjectPtr<UInputMappingContext> GetIMC() const { return IMC; }
	FORCEINLINE TMap<FName, TObjectPtr<UInputAction>> GetInputs() const { return inputsAction; }
	FORCEINLINE TEnumAsByte<EInputEnum> GetState() const { return state; }
};
