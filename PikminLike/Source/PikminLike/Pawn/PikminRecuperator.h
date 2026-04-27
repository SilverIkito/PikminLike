// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pikmin.h"
#include "PikminRecuperator.generated.h"

/**
 * 
 */
UCLASS()
class PIKMINLIKE_API APikminRecuperator : public APikmin
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddPickUp);

public:
	UPROPERTY(BlueprintAssignable) FOnAddPickUp onAddPickUp;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:



	UFUNCTION() void PickUpItem(AActor* _actor);
	UFUNCTION(BlueprintCallable) void CheckGivePickUp();
	void PutItem();

};
