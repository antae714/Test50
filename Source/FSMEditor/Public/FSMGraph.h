// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "FSMGraph.generated.h"

/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class UFSMStateEntryNode> EntryNode;
	UPROPERTY()
	TObjectPtr<class UFSMProcessNode> ProcessNode;
};
