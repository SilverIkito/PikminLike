// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include <PikminLike/Tools/Macro.h>

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");

	billboard->SetupAttachment(mesh);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle _timer;
	//GetWorld()->GetTimerManager().SetTimer(_timer,this, &ASpawner::Spawn,0.5f);

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!actorRef) Spawn();

}

void ASpawner::Spawn()
{
	actorRef = GetWorld()->SpawnActor<AActor>(actorToSpawn, GetActorLocation(), FRotator::ZeroRotator);
}

