// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.h"
#include "FSMState.generated.h"

/** 각상태에서 호출하는 함수명입니다. */ 
namespace StateFunction
{
	static const FName EntryName = FName(TEXT("State Entry"));
	static const FName UpdateName = FName(TEXT("State Update"));
	static const FName ExitName = FName(TEXT("State Exit"));
}

/**
 * BPClass 에서 사용할 상태정보입니다.
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMStateClass : public FFSMElements
{
	GENERATED_BODY()
public:
	friend struct FFSMState;

public:
	/**
	* @brief 상태에맞는 함수를 세팅해줍니다.
	* @param 함수이름입니다. StateFunction 네임스페이스를 사용하세요.
	* @param 함수입니다.
	*/
	void SettingFunction(FName FunctionName, UFunction* func);

protected:
	UPROPERTY()
	TObjectPtr<UFunction> StateEntry;
	UPROPERTY()
	TObjectPtr<UFunction> StateUpdate;
	UPROPERTY()
	TObjectPtr<UFunction> StateExit;

public:
	/** 연결된 전이들의 GUID입니다. */
	UPROPERTY()
	TArray<FGuid> ConnectedTransitionGUID;
};

/**
 * 실제 상태입니다.
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMState : public FFSMElements
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
	/** 소유중인 상태머신 입니다. */
	UFiniteStateMachine* OwningStateMachine;
};