// Fill out your copyright notice in the Description page of Project Settings.


#include "SightComponent.h"
#include "../Tools/Macro.h"

// Sets default values for this component's properties
USightComponent::USightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USightComponent::Sight()
{
	FVector _pos = GetOwner()->GetActorLocation();
	FHitResult _result;
	bool _hit = UKSL::SphereTraceSingleForObjects(this, _pos, _pos, radius,
		channel, false, {},EDrawDebugTrace::None, _result,true);

	if (_hit)
	{
		onDetect.Broadcast(_result.GetActor());
	}
}

