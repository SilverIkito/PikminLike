// Fill out your copyright notice in the Description page of Project Settings.


#include "InfoLevelWorldSubsystem.h"

void UInfoLevelWorldSubsystem::AddOnion(TObjectPtr<AOnion> _onion)
{
	if (!_onion) return;
	onionRef = _onion;
}

void UInfoLevelWorldSubsystem::AddItemCollect(TObjectPtr<AItemCollect> _item)
{
	if (!_item) return;
	if (allItemCollect.Contains(_item)) return;
	allItemCollect.Add(_item);
}

void UInfoLevelWorldSubsystem::RemoveItemCollect(TObjectPtr<AItemCollect> _item)
{
	if (!_item) return;
	allItemCollect.Remove(_item);
}

void UInfoLevelWorldSubsystem::AddPikmin(TObjectPtr<APikmin> _pikmin)
{
	if (!_pikmin) return;
	if (allPikmin.Contains(_pikmin)) return;
	allPikmin.Add(_pikmin);
}
