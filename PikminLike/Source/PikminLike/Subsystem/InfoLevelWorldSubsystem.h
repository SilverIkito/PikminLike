// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <PikminLike/GPE/Onion.h>
#include "InfoLevelWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PIKMINLIKE_API UInfoLevelWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	UPROPERTY() TObjectPtr<AOnion> onionRef = nullptr;

public:
	TObjectPtr<AOnion> GetOnionRef() const { return onionRef; }

public:
	void AddOnion(TObjectPtr<AOnion> _onion);
};
