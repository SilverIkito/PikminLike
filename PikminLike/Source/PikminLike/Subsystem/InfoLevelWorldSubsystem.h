// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <PikminLike/GPE/Onion.h>
#include <PikminLike/Pawn/Pikmin.h>
#include "../GPE/ItemCollect.h"
#include "InfoLevelWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PIKMINLIKE_API UInfoLevelWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TArray<TObjectPtr<APikmin>> allPikmin = {};
	UPROPERTY() TArray<TObjectPtr<AItemCollect>> allItemCollect = {};
	UPROPERTY() TObjectPtr<AOnion> onionRef = nullptr;

public:
	FORCEINLINE TObjectPtr<AOnion> GetOnionRef() const { return onionRef; }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetSize() const { return allPikmin.Num(); }
	UFUNCTION(BlueprintCallable) FORCEINLINE int GetSizeItemCollect() const { return allItemCollect.Num(); }

public:
	void AddOnion(TObjectPtr<AOnion> _onion);
	void AddItemCollect(TObjectPtr<AItemCollect> _item);
	void RemoveItemCollect(TObjectPtr<AItemCollect> _item);
	void AddPikmin(TObjectPtr<APikmin> _pikmin);
};
