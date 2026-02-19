// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoLevelWorldSubsystem.h"

void UInfoLevelWorldSubsystem::AddOnion(TObjectPtr<AOnion> _onion)
{
	if (!_onion) return;
	onionRef = _onion;
}
