// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pikmin.h"
#include "PikminKamikaze.generated.h"

/**
 * 
 */
UCLASS()
class PIKMINLIKE_API APikminKamikaze : public APikmin
{
	GENERATED_BODY()
	


protected:
	virtual void BeginPlay() override;


	UFUNCTION() void Explosion(AActor* _target);
};
