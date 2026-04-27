// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Spawner.generated.h"

UCLASS()
class PIKMINLIKE_API ASpawner : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh;
	UPROPERTY(EditAnywhere) TObjectPtr<UBillboardComponent> billboard;
	UPROPERTY(VisibleAnywhere) TObjectPtr<AActor> actorRef;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> actorToSpawn;
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Spawn();

};
