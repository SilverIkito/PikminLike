// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoLevelWorldSubsystem.h"

void UInfoLevelWorldSubsystem::AddOnion(TObjectPtr<AOnion> _onion)
{
	if (!_onion) return;
	onionRef = _onion;
}

void UInfoLevelWorldSubsystem::AddPikmin(TObjectPtr<APikmin> _pikmin)
{
	if (!_pikmin) return;
	if (allPikmin.Contains(_pikmin)) return;
	allPikmin.Add(_pikmin);
}
