// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FiniteStateMachine.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FSM_API UFiniteStateMachine : public UObject//, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UFiniteStateMachine();

	TArray<struct FFSMState> State;
	TArray<struct FFSMTransition> Transition;

	FFSMState EnteryState;
};


