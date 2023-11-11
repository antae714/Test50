// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMTransition.generated.h"

/**
 * 
 */
USTRUCT()
struct FSM_API FFSMTransition
{
	GENERATED_BODY()
public:
	TObjectPtr<struct FFSMState> m_OwnedNode;
	TObjectPtr<struct FFSMState> m_NextNode;
	FString m_Name;
};


UCLASS()
class UFSMTransitionUtil : public UObject
{
	GENERATED_BODY()
public:
	static bool CheckTransitionCondition(bool transition);
};