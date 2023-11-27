// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMTransition.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"

void FFSMTransition::Init(FFSMTransitionClass* StateClass)
{
	FFSMElements::Init(StateClass->Name, StateClass->CompiledNodeGuid);
}

void FFSMTransition::SettingConnection(class UFiniteStateMachine* _stateMachine, struct FFSMTransitionClass* _TransitionClass)
{
	FFSMState* _NextNode = _stateMachine->States.FindByKey(_TransitionClass->NextNodeGUID);
	if (_NextNode) {
		NextNode = _NextNode;
	}

	TransitionCondition = _TransitionClass->TransitionCondition;

	OwningStateMachine = _stateMachine;
}

bool FFSMTransition::ExecuteTransitionCondition()
{
	bool bTransitionCondition = false;
	FProperty* prop = TransitionCondition->GetReturnProperty();
	OwningStateMachine->ProcessEvent(TransitionCondition, &bTransitionCondition);
	return bTransitionCondition;
}
