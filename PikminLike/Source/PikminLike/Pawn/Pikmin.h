// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <PikminLike/Component/SightComponent.h>
#include <PikminLike/GPE/ItemCollect.h>
#include <PikminLike/GPE/Onion.h>
#include "Pikmin.generated.h"

UCLASS()
class PIKMINLIKE_API APikmin : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddTargetToFollow);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetTarget);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssaut);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddPickUp);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess=true)) TObjectPtr<USightComponent> sight = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) bool canMove = true;

	UPROPERTY(EditAnywhere) float acceptenceRadius = 100;
	UPROPERTY(EditAnywhere) FVector offset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere) TObjectPtr<AItemCollect> itemToPickUp = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<AOnion> onionRef = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnAddTargetToFollow onAddTargetToFollow;
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnResetTarget onResetTarget;
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnAssaut onAssaut;
	UPROPERTY(EditAnywhere, BlueprintAssignable) FOnAddPickUp onAddPickUp;

public:
	APikmin();

public:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	void SetTargetToFollow(AActor* _actor);
	void ResetTarget();
	void PutItem();
	UFUNCTION(BlueprintCallable) void MoveToTarget();
	UFUNCTION(BlueprintCallable) void MoveToDestination(FVector _destination);
	UFUNCTION(BlueprintCallable) void MoveForward();
	UFUNCTION(BlueprintCallable) void Rotate(FVector _destination);
	UFUNCTION() void PickUpItem(AActor* _actor);
	UFUNCTION(BlueprintCallable) void CheckGivePickUp();
};
