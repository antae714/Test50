// Fill out your copyright notice in the Description page of Project Settings.


#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "FSMTransition.h"
#include "FSMBlueprintGeneratedClass.h"

void FFiniteStateMachineHandler::Init(UObject* outer)
{
	FSMInstance = NewObject<UFiniteStateMachine>(outer, FSMClass);
	FSMInstance->Init();
}

UFiniteStateMachine::UFiniteStateMachine()
{
}

void UFiniteStateMachine::Tick(float DeltaTime)
{
	TickEvent(DeltaTime);

	if (!CurrrentState) return;
	int count = 0;
	FFSMState* temp = nullptr;
	do
	{
		temp = CurrrentState;
		UpdateState();
		TransitionState();
	} while (temp != CurrrentState && count >= MaxTransitionsPerFrame);
}

TStatId UFiniteStateMachine::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UFiniteStateMachine, STATGROUP_Tickables);
}

bool UFiniteStateMachine::IsTickable() const
{
	return !this->IsDefaultSubobject();
}

void UFiniteStateMachine::Init()
{
	UFSMBlueprintGeneratedClass* FSMclass = Cast<UFSMBlueprintGeneratedClass>(GetClass());

	States.SetNum(FSMclass->States.Num());
	Transitions.SetNum(FSMclass->Transitions.Num());

	for (int i = 0; i < States.Num(); i++)
	{
		States[i].Init(&FSMclass->States[i]);
	}
	for (int i = 0; i < Transitions.Num(); i++)
	{
		Transitions[i].Init(&FSMclass->Transitions[i]);
	}

	for (int i = 0; i < States.Num(); i++)
	{
		States[i].SettingConnection(this, &FSMclass->States[i]);
	}
	for (int i = 0; i < Transitions.Num(); i++)
	{
		Transitions[i].SettingConnection(this, &FSMclass->Transitions[i]);
	}


	CurrrentState = States.FindByKey(FSMclass->EnteryStateGUID);
	CurrrentState->ExecuteStateEntry();
}

void UFiniteStateMachine::UpdateState()
{
	CurrrentState->ExecuteStateUpdate();
}

void UFiniteStateMachine::TransitionState()
{
	for (auto& item : CurrrentState->ConnectedTransitions)
	{
		if (item->ExecuteTransitionCondition())
		{
			CurrrentState->ExecuteStateExit();
			CurrrentState = item->NextNode;
			CurrrentState->ExecuteStateEntry();
		}
	}
}
