// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <PikminLike/Tools/Macro.h>
#include <PikminLike/Controller/DynamicPlayerController.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	GET_PLAYER_CONTROLLER(_controller);

	TObjectPtr<UEnhancedInputComponent> _component = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	_controller->BindActions(_component, EInputEnum::PLAYER,
	{
		FBindingData(this,"Movement", "MovePlayer", ETriggerEvent::Triggered),
		FBindingData(this,"CameraRotate", "RotatePlayer", ETriggerEvent::Triggered),
		
	});

	ChangeInputState(EInputEnum::PLAYER);

}

void APlayerCharacter::MovePlayer(const FInputActionValue& _value)
{
	const FVector2D& _vector = _value.Get<FVector2D>();
	TObjectPtr<ACharacter> _character = PLAYER_CHARACTER;
	const FRotator& _rotation = _character->GetControlRotation();

	const FVector& _rightVector = UKML::GetRightVector(FRotator(0, _rotation.Yaw, _rotation.Roll));
	const FVector& _forwardVector = UKML::GetForwardVector(FRotator(0, _rotation.Yaw, 0));

	_character->AddMovementInput(_forwardVector, _vector.X);
	_character->AddMovementInput(_rightVector, _vector.Y);

	FVector _inputDirection = (_forwardVector * _vector.X) + (_rightVector * _vector.Y);
	_inputDirection.Normalize();

	FRotator _newRotation = FRotationMatrix::MakeFromX(_inputDirection).Rotator();

	FRotator _currentActorRotation = GetActorRotation();
	const float _delta = GetWorld()->GetDeltaSeconds();
	FRotator _rotationLerp = FMath::RInterpTo(_currentActorRotation, _newRotation, _delta, playerRotationSpeed);
	SetActorRotation(FRotator(_rotationLerp.Pitch, _rotationLerp.Yaw, _currentActorRotation.Roll));

}

void APlayerCharacter::RotatePlayer(const FInputActionValue& _value)
{
	const FVector2D& _vector = _value.Get<FVector2D>();
	const float _rotationSpeed = cameraRotationSpeed * DELTATIME;
	if (springArm->bInheritYaw)
		AddControllerYawInput(_vector.X * _rotationSpeed);
}

