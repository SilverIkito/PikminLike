// Fill out your copyright notice in the Description page of Project Settings.


#include "PikminKamikaze.h"
#include <AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BrainComponent.h"

void APikminKamikaze::BeginPlay()
{
	Super::BeginPlay();
	sight->onDetect.AddDynamic(this, &APikminKamikaze::Explosion);
}

void APikminKamikaze::Explosion(AActor* _target)
{
	_target->Destroy();
	SetLifeSpan(0.05f);
}
