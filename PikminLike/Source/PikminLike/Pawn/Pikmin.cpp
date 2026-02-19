// Fill out your copyright notice in the Description page of Project Settings.


#include "Pikmin.h"
#include <AIController.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "../Tools/Macro.h"

APikmin::APikmin()
{
 	PrimaryActorTick.bCanEverTick = true;
	ADD_COMPONENT(sight, USightComponent, "Sight");

}

void APikmin::BeginPlay()
{
	Super::BeginPlay();
	
}

void APikmin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APikmin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APikmin::SetTarget(AActor* _actor)
{
	if (!_actor) return;
	target = _actor;
	onAddTarget.Broadcast(_actor);
}

void APikmin::ResetTarget()
{
	target = nullptr;
	AAIController* _controller = Cast<AAIController>(GetController());
	_controller->StopMovement();
	onResetTarget.Broadcast();
}

void APikmin::MoveToTarget()
{
	AAIController* _controller = Cast<AAIController>(GetController());

	_controller->MoveToActor(target, acceptenceRadius);
	
}

void APikmin::MoveToDestination(FVector _destination)
{
	AAIController* _controller = Cast<AAIController>(GetController());

	_controller->MoveToLocation(_destination, acceptenceRadius);
}
                             
void APikmin::MoveForward()
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * DELTATIME * 1000);
}

void APikmin::Rotate(FVector _destination)
{
	FRotator _rot = UKML::FindLookAtRotation(GetActorLocation(), _destination);

	SetActorRotation(_rot);
}

void APikmin::PickUpItem(AActor* _actor)
{
	_actor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

