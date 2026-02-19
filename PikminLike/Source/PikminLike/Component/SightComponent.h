// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PIKMINLIKE_API USightComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetect, AActor*, _actor);
	UPROPERTY(EditAnywhere) float radius = 75;
	UPROPERTY(EditAnywhere) bool canSight = true;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> channel;
public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintReadWrite) FOnDetect onDetect;
public:	
	USightComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	UFUNCTION(BlueprintCallable) void Sight();
};
