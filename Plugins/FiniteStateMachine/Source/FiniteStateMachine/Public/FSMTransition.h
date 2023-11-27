// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMTransition.generated.h"


USTRUCT()
struct FINITESTATEMACHINE_API FFSMTransitionClass : public FFSMElements
{
	GENERATED_BODY()
public:
	friend struct FFSMTransition;

public:
	void SettingFunction(UFunction* func)
	{
		TransitionCondition = func;
	}


public:
	UPROPERTY()
	TObjectPtr<UFunction> TransitionCondition;

public:
	UPROPERTY()
	FGuid NextNodeGUID;
};


/**
 * 
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMTransition : public FFSMElements
{
	GENERATED_BODY()
public:
	friend struct FFSMTransitionClass;

public:
	void Init(struct FFSMTransitionClass* StateClass);
	void SettingConnection(class UFiniteStateMachine* _stateMachine, struct FFSMTransitionClass* _TransitionClass);

	bool ExecuteTransitionCondition();

public:
	TObjectPtr<struct FFSMState> NextNode;

protected:
	TObjectPtr<UFunction> TransitionCondition;

protected:
	UFiniteStateMachine* OwningStateMachine;
};

