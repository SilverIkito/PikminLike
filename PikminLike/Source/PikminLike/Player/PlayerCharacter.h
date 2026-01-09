// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <PikminLike/Tools/Macro.h>
#include <PikminLike/Controller/DynamicPlayerController.h>
#include "PlayerCharacter.generated.h"

UCLASS()
class PIKMINLIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera;

	UPROPERTY(EditAnywhere) float playerSpeed = 100;
	UPROPERTY(EditAnywhere) float playerRotationSpeed = 25;
	UPROPERTY(EditAnywhere) float cameraRotationSpeed = 100;

public:
	APlayerCharacter();
	UFUNCTION(BlueprintCallable) FORCEINLINE void ChangeInputState(TEnumAsByte<EInputEnum> _state) const
	{
		GET_PLAYER_CONTROLLER(_controller);
		_controller->SwitchInputState(_state);
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION() void MovePlayer(const FInputActionValue& _value);
	UFUNCTION() void RotatePlayer(const FInputActionValue& _value);
};
