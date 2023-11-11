// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMState.h"

//const FName FFSMState::StateEntryName(TEXT("State Entry"));
//const FName FFSMState::StateUpdateName(TEXT("State Update"));
//const FName FFSMState::StateExitName(TEXT("State Exit"));

void FFSMState::Init(InitArgs arg)
{
	m_Name = arg.Name;
	m_CompiledNodeGuid = arg.CompiledNodeGuid;
}

void FFSMState::SettingFunction(FName FunctionName, UFunction* func)
{
	if (FunctionName == StateEntryName)
	{
		StateEntry = func;
	}
	else if (FunctionName == StateUpdateName)
	{
		StateUpdate = func;
	}
	else if (FunctionName == StateExitName)
	{
		StateExit = func;
	}
	else
	{
		ensure(0);
	}
}
