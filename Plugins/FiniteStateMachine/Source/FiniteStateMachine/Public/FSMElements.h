// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMElements.generated.h"



/**
 * 
 */
USTRUCT()
struct FINITESTATEMACHINE_API FFSMElements
{
	GENERATED_BODY()
public:
	void Init(FString _Name, FGuid _CompiledNodeGuid);
	bool operator==(FGuid _NodeGuid);

protected:
	/** 노드의 이름입니다. */
	UPROPERTY()
	FString Name;
	/** 컴파일당시의 노드의 GUID입니다. */
	UPROPERTY()
	FGuid CompiledNodeGuid;
};
