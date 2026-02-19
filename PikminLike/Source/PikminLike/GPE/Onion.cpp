// Fill out your copyright notice in the Description page of Project Settings.


#include "Onion.h"
#include "../Tools/Macro.h"
#include <PikminLike/Subsystem/InfoLevelWorldSubsystem.h>

// Sets default values
AOnion::AOnion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CDS(RootComponent, USceneComponent, "Root");

	ATTACH_TO(mesh, UStaticMeshComponent, "Mesh", RootComponent);
	ATTACH_TO(billboard, UBillboardComponent, "Billboard",RootComponent);
}

// Called when the game starts or when spawned
void AOnion::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UInfoLevelWorldSubsystem>()->AddOnion(this);

}

// Called every frame
void AOnion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

