// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemCollect.generated.h"

UCLASS()
class PIKMINLIKE_API AItemCollect : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) bool canTake = true;
	
public:
	FORCEINLINE bool CanTake() const { return canTake; }
	FORCEINLINE void SetCanTake(bool _value) { canTake = _value; }

public:	
	// Sets default values for this actor's properties
	AItemCollect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
