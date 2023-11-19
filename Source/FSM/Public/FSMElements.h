// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.generated.h"

/**
 * 
 */
USTRUCT()
struct FSM_API FFSMElements
{
	GENERATED_BODY()
public:
	void Init(FString _Name, FGuid _CompiledNodeGuid);
	bool operator==(FGuid _NodeGuid);

protected:
	UPROPERTY()
	FString Name;
	UPROPERTY()
	FGuid CompiledNodeGuid;
};
