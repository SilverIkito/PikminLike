// Fill out your copyright notice in the Description page of Project Settings.


#include "Pikmin.h"

// Sets default values
APikmin::APikmin()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	skeletal = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal");
	capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
	
	skeletal->SetupAttachment(RootComponent);
	capsule->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APikmin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APikmin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APikmin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

