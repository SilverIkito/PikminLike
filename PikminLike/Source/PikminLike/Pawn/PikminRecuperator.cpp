// Fill out your copyright notice in the Description page of Project Settings.


#include "PikminRecuperator.h"
#include <PikminLike/Tools/Macro.h>
#include <PikminLike/Subsystem/InfoLevelWorldSubsystem.h>



void APikminRecuperator::BeginPlay()
{
	Super::BeginPlay();
	sight->onDetect.AddDynamic(this, &APikminRecuperator::PickUpItem);
}

void APikminRecuperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APikminRecuperator::PickUpItem(AActor* _actor)
{
	if (CAST(AItemCollect, _item, _actor))
	{
		if (!_item->CanTake()) return;
		_item->SetCanTake(false);
		_item->GetComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(false);
		_item->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		itemToPickUp = _item;
		target = onionRef;
		_item->SetActorRelativeLocation(FVector(0, 0, 50));
		onAddPickUp.Broadcast();
	}
}

void APikminRecuperator::CheckGivePickUp()
{
	if (!itemToPickUp) return;
	if (!onionRef)
	{
		LOG_WARN("No onionRef");
		return;
	}
	FRAME_LOG(FString::SanitizeFloat(FVector::Dist(GetActorLocation(), onionRef->GetActorLocation())));

	if (FVector::Dist(GetActorLocation(), onionRef->GetActorLocation()) < 200)
	{
		GetWorld()->GetSubsystem<UInfoLevelWorldSubsystem>()->RemoveItemCollect(itemToPickUp);
		itemToPickUp->Destroy();
		itemToPickUp = nullptr;
		SetTargetToFollow(onionRef->GetLocInPosToGo());
	}
}

void APikminRecuperator::PutItem()
{
	itemToPickUp->GetComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
	itemToPickUp->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	itemToPickUp->SetCanTake(true);

	FHitResult _result;
	bool _hit = UKSL::LineTraceSingle(this, GetActorLocation() + GetActorForwardVector() * 150, GetActorLocation() + GetActorForwardVector() * 150 - FVector(0, 0, 200),
		ETraceTypeQuery::TraceTypeQuery1, false, {}, EDrawDebugTrace::ForDuration, _result, true);
	if (_hit)
		itemToPickUp->SetActorLocation(_result.ImpactPoint + FVector(0, 0, 20));
	itemToPickUp = nullptr;
}