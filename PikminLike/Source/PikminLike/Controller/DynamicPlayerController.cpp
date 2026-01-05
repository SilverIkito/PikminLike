// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPlayerController.h"
#include <EnhancedInputSubsystems.h>
#include "../DataAsset/InputsDataAsset.h"
#include "../Tools/Macro.h"

ADynamicPlayerController::ADynamicPlayerController()
{

}

void ADynamicPlayerController::BeginPlay()
{
	Super::BeginPlay();
	LoadDataAssets();
}

void ADynamicPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void ADynamicPlayerController::BeginDestroy()
{
	Super::BeginDestroy();
}

void ADynamicPlayerController::LoadDataAssets()
{
	if (hasBeenInit) return;

	int _size = allDataAssets.Num();

	for (int _i = 0; _i < _size; _i++)
	{
		TObjectPtr<UInputsDataAsset> _data = allDataAssets[_i];
		if (!_data) continue;
		const EInputEnum& _state = _data->GetState();
		const TMap<FName, TObjectPtr<UInputAction>>& _inputs = _data->GetInputs();
		const TObjectPtr<UInputMappingContext>& _IMC = _data->GetIMC();

		inputsData.Add(_state, FInputStruct(_inputs, _IMC));
	}
	hasBeenInit = true;
}

void ADynamicPlayerController::DesactivateInput()
{
	UEnhancedInputLocalPlayerSubsystem* _sub = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_sub) return;

	_sub->ClearAllMappings();
}

void ADynamicPlayerController::SwitchInputState(const TEnumAsByte<EInputEnum>& _state)
{
	if (!inputsData.Contains(_state)) return;
	UEnhancedInputLocalPlayerSubsystem* _sub = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_sub) return;

	_sub->ClearAllMappings();

	bool _hasPreviousState = inputsData.Contains(currentState);
	if (_hasPreviousState)
	{
		FInputStruct _oldData = inputsData[currentState];
		_sub->RemoveMappingContext(_oldData.IMC);
	}

	FInputStruct _data = inputsData[_state];
	_sub->AddMappingContext(_data.IMC, 0);

	currentState = _state;
}

FInputStruct ADynamicPlayerController::GetStateInputs(const TEnumAsByte<EInputEnum>& _state)
{
	if (!inputsData.Contains(_state)) return FInputStruct();

	return inputsData[_state];
}

void ADynamicPlayerController::BindActions(UEnhancedInputComponent* _inputComponent, const TEnumAsByte<EInputEnum>& _state, const TArray<FBindingData>& _bindings)
{
	LoadDataAssets();
	if (!inputsData.Contains(_state)) return;

	FInputStruct _data = inputsData[_state];

	int _size = _bindings.Num();

	for (int _i = 0; _i < _size; _i++)
	{
		const FBindingData& _binding = _bindings[_i];

		UFunction* _func = _binding.objectReference->FindFunction(_binding.methodName);
		if (!_func)
		{
			LOG("Wrong method name => " + _binding.methodName.ToString() + " from binding " + _binding.objectReference->GetName());
			continue;
		}
		UInputAction* _action = _data.GetInputFromKey(_binding.actionName);
		if (!_action)
		{
			LOG("Wrong action name => " + _binding.actionName.ToString() + " from binding " + _binding.objectReference->GetName());
			continue;
		}

		_inputComponent->BindAction(_action, _binding.triggerType, _binding.objectReference, _binding.methodName);
	}
}
