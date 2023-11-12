// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMState.generated.h"


/**
 * 
 */
USTRUCT()
struct FSM_API FFSMState : public FFSMElements
{
	GENERATED_BODY()

public:
	inline static const FName StateEntryName = FName(TEXT("State Entry"));
	inline static const FName StateUpdateName = FName(TEXT("State Update"));
	inline static const FName StateExitName = FName(TEXT("State Exit"));

	void SettingFunction(FName FunctionName, UFunction* func);


	bool operator==(FGuid _NodeGuid) { return m_CompiledNodeGuid == _NodeGuid; }

protected:
	UPROPERTY()
	TObjectPtr<UFunction> StateEntry;
	UPROPERTY()
	TObjectPtr<UFunction> StateUpdate;
	UPROPERTY()
	TObjectPtr<UFunction> StateExit;

public:
	UPROPERTY()
	TArray<FGuid> m_ConnectedTransitionGUID;
	
	TArray<struct FFSMTransition*> m_ConnectedTransition;
};