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

}

void APikmin::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UInfoLevelWorldSubsystem> _sub = GetWorld()->GetSubsystem<UInfoLevelWorldSubsystem>();
	onionRef = _sub->GetOnionRef();
	_sub->AddPikmin(this);
	sight->onDetect.AddDynamic(this, &APikmin::PickUpItem);
	
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
	if (itemToPickUp)
		PutItem();
		
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

void APikmin::PutItem()
{
	itemToPickUp->GetComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
	itemToPickUp->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	itemToPickUp->SetCanTake(true);

	FHitResult _result;
	//bool _hit = LINETRACE_SINGLE(_result, GetActorLocation() + GetActorForwardVector() * 150, GetActorLocation() + GetActorForwardVector() * 150 - FVector(0,0, -100));
	bool _hit = UKSL::LineTraceSingle(this, GetActorLocation() + GetActorForwardVector() * 150, GetActorLocation() + GetActorForwardVector() * 150 - FVector(0, 0, 200),
		ETraceTypeQuery::TraceTypeQuery1, false, {}, EDrawDebugTrace::ForDuration, _result,true);
	if (_hit)
		itemToPickUp->SetActorLocation(_result.ImpactPoint + FVector(0,0,20));
	itemToPickUp = nullptr;
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
	if (CAST(AItemCollect, _item, _actor))
	{
		if (!_item->CanTake()) return;
		_item->SetCanTake(false);
		_item->GetComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(false);
		_item->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		itemToPickUp = _item;
		target = onionRef;
		_item->SetActorRelativeLocation(FVector(0,0,50));
		onAddPickUp.Broadcast();
	}
}

void APikmin::CheckGivePickUp()
{
	if (!itemToPickUp) return;

	FRAME_LOG(FString::SanitizeFloat(FVector::Dist(GetActorLocation(), onionRef->GetActorLocation())));

	if (FVector::Dist(GetActorLocation(), onionRef->GetActorLocation()) < 200)
	{
		itemToPickUp->Destroy();
		itemToPickUp = nullptr;
		ResetTarget();
	}
}

