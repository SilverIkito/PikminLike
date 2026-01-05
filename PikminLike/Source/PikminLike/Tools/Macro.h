// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/InputSettings.h>

bool CheckDevice(UWorld* _world, const EHardwareDevicePrimaryType& _toCheck);

//Utils
#define WORLD GetWorld()
#define GET_WORLD(variableName) TObjectPtr<UWorld> variableName = WORLD
#define CAST(classType, variableName, variable) TObjectPtr<classType> variableName = Cast<classType>(variable)
#define DELTATIME WORLD->DeltaTimeSeconds
#define SUBSYSTEM(type) WORLD->GetGameInstance()->GetSubsystem<type>()
#define WORLD_SUBSYSTEM(type) WORLD->GetSubsystem<type>()
#define GET_SUBSYSTEM(type, variableName) TObjectPtr<type> variableName = WORLD->GetGameInstance()->GetSubsystem<type>()
#define GET_WORLD_SUBSYSTEM(type, variableName) TObjectPtr<type> variableName = WORLD->GetSubsystem<type>()
#define UKSL UKismetSystemLibrary
#define UKML UKismetMathLibrary
#define ONE_FRAME_DELAY(worldContext, lambdaBody) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() { lambdaBody; }))
#define TIMER(worldContext, handleVariable, lambdaBody, delay) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimer(handleVariable, FTimerDelegate::CreateLambda([this]() { lambdaBody; }), delay, false);
#define TIMER_LOOP(worldContext, handleVariable, lambdaBody, initialDelay, loopDelay) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimer(handleVariable, FTimerDelegate::CreateLambda([this]() { lambdaBody; }), loopDelay, true, initialDelay);
#define GAMEINSTANCE Cast<USR_GameInstance>(WORLD->GetGameInstance())
#define PLAYER_PAWN WORLD->GetFirstPlayerController()->GetPawn()
#define PLAYER_CHARACTER WORLD->GetFirstPlayerController()->GetCharacter()
#define GET_PLAYER_PAWN(variableName) TObjectPtr<APawn> variableName = PLAYER_PAWN
#define GET_PLAYER_CHARACTER(variableName) TObjectPtr<ACharacter> variableName = PLAYER_CHARACTER
#define CDS(variable, type, name) variable = CreateDefaultSubobject<type>(name)
#define ATTACH_TO(variable, type, name, AttachTo) CDS(variable, type, name); variable->SetupAttachment(AttachTo)
#define ADD_COMPONENT(variable, type, name) CDS(variable, type, name); AddOwnedComponent(variable)
#define PLAYER_CONTROLLER Cast<ADynamicPlayerController>(WORLD->GetFirstPlayerController())
#define GET_PLAYER_CONTROLLER(variable) ADynamicPlayerController* variable = PLAYER_CONTROLLER

//Log
#define LOG_CUSTOM(message, color) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::color, 20.0f)
#define LOG(message) LOG_CUSTOM(message, Green)
#define LOG_WARN(message) LOG_CUSTOM(message, Yellow)
#define LOG_ERROR(message) LOG_CUSTOM(message, Red)
#define FRAME_LOG(message) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::Magenta, DELTATIME)

//Debug
#define DEBUG_CUBE(location, size, color) UKSL::DrawDebugBox(WORLD, location, size, FQuat::Identity, color, false, 1.0f)
#define DEBUG_CUBE_TIME(location, size, color, lifeTime) UKSL::DrawDebugBox(WORLD, location, size, FQuat::Identity, color, false, lifeTime)
#define DEBUG_SPHERE(location, radius, color) UKSL::DrawDebugSphere(WORLD, location, radius, 12, color, false, 1.0f)
#define DEBUG_SPHERE_TIME(location, radius, color,lifeTime) UKSL::DrawDebugSphere(WORLD, location, radius, 12, color, false,lifeTime)
#define DEBUG_LINE(startLocation, endLocation, color) UKSL::DrawDebugLine(WORLD, startLocation, endLocation, color, false, 1.0f)
#define DEBUG_LINE_TIME(startLocation, endLocation, color, lifeTime) UKSL::DrawDebugLine(WORLD, startLocation, endLocation, color, false, lifeTime)
#define DEBUG_CONE(location, direction, angle, length, color) UKSL::DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, 1.0f)
#define DEBUG_CONE_TIME(location, direction, angle, length, color, lifeTime) UKSL::DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, lifeTime)
#define DEBUG_RAY(startLocation, direction, length, color) UKSL::DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, 1.0f)
#define DEBUG_RAY_TIME(startLocation, direction, length, color, lifeTime) UKSL::DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, lifeTime)
#define DEBUG_TEXT(location, message, color, lifeTime) UKSL::DrawDebugString(WORLD, location, message, nullptr, color, 1.0f, true)
#define DEBUG_TEXT_TIME(location, message, color, lifeTime) UKSL::DrawDebugString(WORLD, location, message, nullptr, color, lifeTime, true)

//Trace
#define LINETRACE_SINGLE(outHit,start, end) WORLD->LineTraceSingleByChannel(outHit,start,end,ECC_Visibility)
#define LINETRACE_SINGLE_CHANNEL(start,end, channel) FHitResult _result; WORLD->LineTraceSingleByChannel(_result,start,end,channel)
#define LINETRACE_SINGLE_HIT_CHANNEL(outHit,start, end, channel) WORLD->LineTraceSingleByChannel(outHit,start,end,channel)
#define LINETRACE_SINGLE_OBJECT(start, end, channel, debugType, outHit, traceColor, traceHitColor, drawTime) UKSL::LineTraceSingleForObjects(this, start, end, channel, false, {}, debugType, outHit, true, traceColor, traceHitColor, drawTime)
#define LINETRACE_MULTI(outHit,start, end) WORLD->LineTraceMultiByChannel(outHit,start,end,ECC_Visibility)
#define LINETRACE_MULTI_CHANNEL(start,end, channel) TArray<FHitResult> _result; WORLD->LineTraceMultiByChannel(_result,start,end,channel)
#define LINETRACE_MULTI_HIT_CHANNEL(outHit,start, end, channel) WORLD->LineTraceMultiByChannel(outHit,start,end,channel)

#define SPHERETRACE_SINGLE(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceSingle(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_SINGLE_COMPLEX(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceSingle(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI(start,end,radius,channel,outHit) UKSL::SphereTraceMulti(WORLD,start,end,radius,channel,true,{},EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI_COMPLEX(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceMulti(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI_OBJECT(start,end,radius, channel, debugType, outHit, color, drawTime) UKSL::SphereTraceMultiForObjects(this, start, end, radius, channel, false, {}, debugType, outHit, true, color, FLinearColor::Green, drawTime)

//Inputs
#define USE_CONTROLLER CheckDevice(WORLD,EHardwareDevicePrimaryType::Gamepad)
#define USE_KEYBOARD CheckDevice(WORLD,EHardwareDevicePrimaryType::KeyboardAndMouse)