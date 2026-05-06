// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <PikminLike/Component/SightComponent.h>
#include <PikminLike/GPE/ItemCollect.h>
#include <PikminLike/GPE/Onion.h>
#include "NiagaraComponent.h"
#include "Pikmin.generated.h"

UENUM()
enum FTypePikmin
{
	RECUPERATOR,
	KAMIKAZE,
	MAX
};

UCLASS()
class PIKMINLIKE_API APikmin : public ACharacter
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddTargetToFollow);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetTarget);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssaut);

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess=true)) TObjectPtr<USightComponent> sight = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) TObjectPtr<UNiagaraComponent> fx = nullptr;

	UPROPERTY(EditAnywhere) TEnumAsByte<FTypePikmin> type = FTypePikmin::RECUPERATOR;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess), BlueprintReadOnly) bool canMove = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) float timeAssaut = 3;
	UPROPERTY(EditAnywhere) float acceptenceRadius = 100;
	UPROPERTY(EditAnywhere) FVector offset = FVector::ZeroVector;
	UPROPERTY(EditAnywhere) TObjectPtr<AItemCollect> itemToPickUp = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<AOnion> onionRef = nullptr;

	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true)) FTimerHandle timerEndAssaut;


public:
	UPROPERTY(BlueprintAssignable) FOnAddTargetToFollow onAddTargetToFollow;
	UPROPERTY(BlueprintAssignable) FOnResetTarget onResetTarget;
	UPROPERTY(BlueprintAssignable) FOnAssaut onAssaut;
public:
	TEnumAsByte<FTypePikmin> GetTypePikmin() const { return type; }

public:
	APikmin();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	void SetTargetToFollow(AActor* _actor);
	UFUNCTION(BlueprintCallable) void ResetTarget();
	UFUNCTION(BlueprintCallable) void MoveToTarget();
	UFUNCTION(BlueprintCallable) void MoveToDestination(FVector _destination);
	UFUNCTION(BlueprintCallable) void MoveForward();
	UFUNCTION(BlueprintCallable) void Rotate(FVector _destination);
};
