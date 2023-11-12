// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMTransition.generated.h"

/**
 * 
 */
USTRUCT()
struct FSM_API FFSMTransition : public FFSMElements
{
	GENERATED_BODY()

public:
	void SettingFunction(UFunction* func);

	bool operator==(FGuid _NodeGuid) { return m_CompiledNodeGuid == _NodeGuid; }
public:
	UPROPERTY()
	TObjectPtr<UFunction> TransitionCondition;

public:
	TObjectPtr<struct FFSMState> m_OwnedNode;
	TObjectPtr<struct FFSMState> m_NextNode;
};

