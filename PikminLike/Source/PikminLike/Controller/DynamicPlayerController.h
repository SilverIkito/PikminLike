// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <InputMappingContext.h>
#include "EnhancedInputComponent.h"
#include "DynamicPlayerController.generated.h"

class UInputsDataAsset;

UENUM(BlueprintType)
enum EInputEnum
{
	NONE,
	PLAYER,
	ROPE,
	INTERACT_GPE,
	CLIMB,
	OPTION,
	MAP,
	SPYGLASS,
	GLIDER,
	SLACKLINE,
	HOIST,
	NARROW_PASSAGE
};

USTRUCT(BlueprintType)
struct FInputStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TMap<FName, TObjectPtr<UInputAction>> inputsAction;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputMappingContext> IMC;

	FInputStruct() = default;

	FInputStruct(TMap<FName, TObjectPtr<UInputAction>> _inputsAction, TObjectPtr<UInputMappingContext> _IMC)
	{
		inputsAction = _inputsAction;
		IMC = _IMC;
	}

	TObjectPtr<UInputAction> GetInputFromKey(const FName& _key)
	{
		if (!inputsAction.Contains(_key)) return nullptr;

		return inputsAction[_key];
	}
};

USTRUCT(BlueprintType)
struct FBindingData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UObject> objectReference;
	UPROPERTY(EditAnywhere) FName actionName;
	UPROPERTY(EditAnywhere) FName methodName;
	UPROPERTY(EditAnywhere) ETriggerEvent triggerType;

	FBindingData() = default;

	FBindingData(const TObjectPtr<UObject>& _objectReference, const FName& _actionName, const FName& _methodName, const ETriggerEvent& _trigger)
	{
		objectReference = _objectReference;
		actionName = _actionName;
		methodName = _methodName;
		triggerType = _trigger;
	}
};

UCLASS()
class PIKMINLIKE_API ADynamicPlayerController : public APlayerController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TEnumAsByte<EInputEnum> currentState;
	UPROPERTY(VisibleAnywhere) TMap<TEnumAsByte<EInputEnum>, FInputStruct> inputsData;
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<UInputsDataAsset>> allDataAssets;
	bool hasBeenInit = false;
	bool bIsUsingGamepad = false;

public:
	FORCEINLINE TEnumAsByte<EInputEnum> GetCurrentState() const { return currentState; }

	UFUNCTION(BlueprintCallable) FORCEINLINE bool IsUsingGamepad()const {
		return bIsUsingGamepad;
	}
	UFUNCTION(BlueprintCallable) FORCEINLINE void SetIsUsingGamepad(const bool _bIsUsingGamepad) {
		bIsUsingGamepad = _bIsUsingGamepad;
	}

public:
	ADynamicPlayerController();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable) void LoadDataAssets();

	UFUNCTION(BlueprintCallable) void DesactivateInput();

public:
	UFUNCTION(BlueprintCallable) void SwitchInputState(const TEnumAsByte<EInputEnum>& _state);
	UFUNCTION(BlueprintCallable) FInputStruct GetStateInputs(const TEnumAsByte<EInputEnum>& _state);
	UFUNCTION(BlueprintCallable) void BindActions(UEnhancedInputComponent* _inputComponent, const TEnumAsByte<EInputEnum>& _state, const TArray<FBindingData>& _bindings);
};
