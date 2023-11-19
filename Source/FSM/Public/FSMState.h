// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMState.generated.h"

namespace StateFunction
{
	static const FName EntryName = FName(TEXT("State Entry"));
	static const FName UpdateName = FName(TEXT("State Update"));
	static const FName ExitName = FName(TEXT("State Exit"));
}

USTRUCT()
struct FSM_API FFSMStateClass : public FFSMElements
{
	GENERATED_BODY()
public:
	friend struct FFSMState;

public:
	void SettingFunction(FName FunctionName, UFunction* func)
	{
		if (FunctionName == StateFunction::EntryName)
		{
			StateEntry = func;
		}
		else if (FunctionName == StateFunction::UpdateName)
		{
			StateUpdate = func;
		}
		else if (FunctionName == StateFunction::ExitName)
		{
			StateExit = func;
		}
		else
		{
			ensure(0);
		}
	}

protected:
	UPROPERTY()
	TObjectPtr<UFunction> StateEntry;
	UPROPERTY()
	TObjectPtr<UFunction> StateUpdate;
	UPROPERTY()
	TObjectPtr<UFunction> StateExit;

public:
	UPROPERTY()
	TArray<FGuid> ConnectedTransitionGUID;
};

/**
 * 
 */
USTRUCT()
struct FSM_API FFSMState : public FFSMElements
{
	GENERATED_BODY()
public:
	friend struct FFSMStateClass;

public:
	void Init(struct FFSMStateClass* StateClass);
	void SettingConnection(class UFiniteStateMachine* _stateMachine, struct FFSMStateClass* StateClass);

	void ExecuteStateEntry();
	void ExecuteStateUpdate();
	void ExecuteStateExit();

public:
	TArray<struct FFSMTransition*> ConnectedTransitions;

protected:
	TObjectPtr<UFunction> StateEntry;
	TObjectPtr<UFunction> StateUpdate;
	TObjectPtr<UFunction> StateExit;

protected:

	UFiniteStateMachine* OwningStateMachine;
};