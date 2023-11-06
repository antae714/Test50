// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FiniteStateMachine.generated.h"

USTRUCT()
struct FTramsition
{
	GENERATED_BODY()
public:
	FFSMState* m_OwnedNode;
	FFSMState* m_NextNode;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateBeginDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateUpdateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateEndDelegate);

USTRUCT()
struct FFSMState
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FStateBeginDelegate StateBegin;
	UPROPERTY(BlueprintAssignable)
	FStateUpdateDelegate StateUpdate;
	UPROPERTY(BlueprintAssignable)
	FStateEndDelegate StateEnd;
public:
	TArray<FTramsition> m_ConnectedTransition;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FSM_API UFiniteStateMachine : public UObject//, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UFiniteStateMachine();

	TArray<FFSMState> m_State;
	TArray<FTramsition> m_Transition;

	FFSMState* EnteryState;
};
