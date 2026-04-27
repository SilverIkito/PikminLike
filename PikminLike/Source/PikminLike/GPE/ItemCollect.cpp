// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCollect.h"
#include <PikminLike/Tools/Macro.h>
#include <PikminLike/Subsystem/InfoLevelWorldSubsystem.h>

// Sets default values
AItemCollect::AItemCollect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CDS(mesh, UStaticMeshComponent, "mesh");
}

// Called when the game starts or when spawned
void AItemCollect::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetSubsystem<UInfoLevelWorldSubsystem>()->AddItemCollect(this);
	
}

// Called every frame
void AItemCollect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



