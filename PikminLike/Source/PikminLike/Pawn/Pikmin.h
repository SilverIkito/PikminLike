// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <PikminLike/Component/SightComponent.h>
#include "Pikmin.generated.h"

UCLASS()
class PIKMINLIKE_API APikmin : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddTarget, AActor*, _target);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetTarget);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssaut);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess=true)) TObjectPtr<USightComponent> sight = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) bool canMove = true;

	UPROPERTY(EditAnywhere) float acceptenceRadius = 100;
	UPROPERTY(EditAnywhere) FVector offset = FVector::ZeroVector;

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnAddTarget onAddTarget;
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnResetTarget onResetTarget;
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnAssaut onAssaut;

public:
	APikmin();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	void SetTarget(AActor* _actor);
	void ResetTarget();
	UFUNCTION(BlueprintCallable) void MoveToTarget();
	UFUNCTION(BlueprintCallable) void MoveToDestination(FVector _destination);
	UFUNCTION(BlueprintCallable) void MoveForward();
	UFUNCTION(BlueprintCallable) void Rotate(FVector _destination);
	UFUNCTION(BlueprintCallable) void PickUpItem(AActor* _actor);
};
