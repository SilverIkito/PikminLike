// Fill out your copyright notice in the Description page of Project Settings.


#include "Pikmin.h"
#include <AIController.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "../Tools/Macro.h"
#include "../Player/PlayerCharacter.h"
#include <PikminLike/Subsystem/InfoLevelWorldSubsystem.h>

APikmin::APikmin()
{
 	PrimaryActorTick.bCanEverTick = true;
	ADD_COMPONENT(sight, USightComponent, "Sight");
	ATTACH_TO(fx, UNiagaraComponent, "FX", RootComponent);
}

void APikmin::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UInfoLevelWorldSubsystem> _sub = GetWorld()->GetSubsystem<UInfoLevelWorldSubsystem>();
	onionRef = _sub->GetOnionRef();
	_sub->AddPikmin(this);
	
}

void APikmin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APikmin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APikmin::SetTargetToFollow(AActor* _actor)
{
	if (!_actor) return;
		
	target = _actor;
	onAddTargetToFollow.Broadcast();
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

