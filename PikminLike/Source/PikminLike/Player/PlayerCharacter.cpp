// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <PikminLike/Tools/Macro.h>
#include <PikminLike/Controller/DynamicPlayerController.h>
#include <PikminLike/Pawn/Pikmin.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	meshCursor = CreateDefaultSubobject<UStaticMeshComponent>("MeshCursor");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	meshCursor->SetupAttachment(RootComponent);
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
			FBindingData(this,"StartMove", "StartMove", ETriggerEvent::Started),
			FBindingData(this,"EndMove", "EndMove", ETriggerEvent::Completed),
			FBindingData(this,"CameraRotate", "RotatePlayer", ETriggerEvent::Triggered),
			FBindingData(this,"Call", "Call", ETriggerEvent::Started),
			FBindingData(this,"StopPikmin", "StopPikmin", ETriggerEvent::Started),
			FBindingData(this,"Assaut", "Assaut", ETriggerEvent::Started),
			FBindingData(this,"SendPikmin", "SendPikmin", ETriggerEvent::Started),
			
	});

	ChangeInputState(EInputEnum::PLAYER);

}

APikmin* APlayerCharacter::GetCloserPikmin()
{
	int _size = allPikminFollow.Num();
	if(_size == 0) return nullptr;
	if (_size == 1) return allPikminFollow[0];

	float _minDist = FVector::Dist(GetActorLocation(), allPikminFollow[0]->GetActorLocation());
	int _index = 0;
	for (int i = 0; i < _size; i++)
	{
		float _dist = FVector::Dist(GetActorLocation(), allPikminFollow[i]->GetActorLocation());
		if (_dist < _minDist)
		{
			_minDist = _dist;
			_index = i;
		}
	}

	return allPikminFollow[_index];
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

void APlayerCharacter::StartMove(const FInputActionValue& _value)
{
	onStartMove.Broadcast();
}

void APlayerCharacter::EndMove(const FInputActionValue& _value)
{
	onEndMove.Broadcast();
}

void APlayerCharacter::RotatePlayer(const FInputActionValue& _value)
{
	const FVector2D& _vector = _value.Get<FVector2D>();
	const float _rotationSpeed = cameraRotationSpeed * DELTATIME;
	if (springArm->bInheritYaw)
		AddControllerYawInput(_vector.X * _rotationSpeed);
}

void APlayerCharacter::Call(const FInputActionValue& _value)
{
	TArray<FHitResult> _result;
	bool _hit = SPHERETRACE_MULTI_OBJECT(meshCursor->GetComponentLocation(),
		meshCursor->GetComponentLocation(), radiusCall,
		typeCall, EDrawDebugTrace::ForDuration, _result, FLinearColor::Blue, 2);

	int _size = _result.Num();

	for (int i = 0; i < _size; i++)
	{
		APikmin* _pikmin = Cast<APikmin>(_result[i].GetActor());
		if (_pikmin)
		{
			if (allPikminFollow.Contains(_pikmin))continue;
			
			_pikmin->SetTargetToFollow(this);
			allPikminFollow.Add(_pikmin);
		}
	}
	onCurrentPikminUpdate.Broadcast(allPikminFollow.Num());
}

void APlayerCharacter::StopPikmin(const FInputActionValue& _value)
{
	LOG("STOP pikmin");
	int _size = allPikminFollow.Num();
	for (int i = 0; i < _size; i++)
	{
		allPikminFollow[i]->ResetTarget();
	}
	allPikminFollow.Empty();
	onCurrentPikminUpdate.Broadcast(allPikminFollow.Num());
}

void APlayerCharacter::SendPikmin(const FInputActionValue& _value)
{
	APikmin* _pikminToSend = GetCloserPikmin();
	if (!_pikminToSend) return;

	_pikminToSend->ResetTarget();
	_pikminToSend->Rotate(meshCursor->GetComponentLocation());
	_pikminToSend->onAssaut.Broadcast();

	allPikminFollow.Remove(_pikminToSend);
	onCurrentPikminUpdate.Broadcast(allPikminFollow.Num());
}

void APlayerCharacter::Assaut(const FInputActionValue& _value)
{
	if (allPikminFollow.Num() == 0 || isAssaut) return;
	isAssaut = true;
	GetWorld()->GetTimerManager().SetTimer(timerAssaut, this, &APlayerCharacter::AssautLoop, 0.05f, true);

}

void APlayerCharacter::AssautLoop()
{
	if (allPikminFollow.Num() == 0)
	{
		isAssaut = false;
		GetWorld()->GetTimerManager().ClearTimer(timerAssaut);
		return;
	}
	SendPikmin(FInputActionValue());
}

