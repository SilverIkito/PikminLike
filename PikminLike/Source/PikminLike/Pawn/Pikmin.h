// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/CapsuleComponent.h>
#include "Pikmin.generated.h"

UCLASS()
class PIKMINLIKE_API APikmin : public APawn
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) TObjectPtr<USkeletalMeshComponent> skeletal = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UCapsuleComponent> capsule = nullptr;

public:
	// Sets default values for this pawn's properties
	APikmin();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
