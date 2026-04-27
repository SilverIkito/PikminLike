// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Onion.generated.h"

UCLASS()
class PIKMINLIKE_API AOnion : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBillboardComponent> billboard = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<AActor> posToGo = nullptr;

public:
	FORCEINLINE TObjectPtr<AActor> GetLocInPosToGo() { return posToGo; }

public:	
	AOnion();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
