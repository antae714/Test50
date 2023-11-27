// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMState.h"
#include "FiniteStateMachine.h"

void FFSMStateClass::SettingFunction(FName FunctionName, UFunction* func)
{
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
}

void FFSMState::Init(FFSMStateClass* StateClass)
{
	FFSMElements::Init(StateClass->Name, StateClass->CompiledNodeGuid);
}

void FFSMState::SettingConnection(class UFiniteStateMachine* _stateMachine, struct FFSMStateClass* StateClass)
{

	for (auto& item : StateClass->ConnectedTransitionGUID)
	{
		FFSMTransition* ConectedTransition = _stateMachine->Transitions.FindByKey(item);
		if (ConectedTransition) {
			ConnectedTransitions.Add(ConectedTransition);
		}
	}

	StateEntry = StateClass->StateEntry;
	StateUpdate = StateClass->StateUpdate;
	StateExit = StateClass->StateExit;


	OwningStateMachine = _stateMachine;
}

void FFSMState::ExecuteStateEntry()
{
	if (StateEntry)
	{
		OwningStateMachine->ProcessEvent(StateEntry, nullptr);
	}
}

void FFSMState::ExecuteStateUpdate()
{
	if (StateUpdate)
	{
		OwningStateMachine->ProcessEvent(StateUpdate, nullptr);
	}
}

void FFSMState::ExecuteStateExit()
{
	if (StateExit)
	{
		OwningStateMachine->ProcessEvent(StateExit, nullptr);
	}
}
