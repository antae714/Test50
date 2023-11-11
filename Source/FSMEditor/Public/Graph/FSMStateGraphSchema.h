// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "FSMStateGraphSchema.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateDelegate);
/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMStateGraphSchema : public UEdGraphSchema_K2
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FStateDelegate StateEnd;
#pragma region UEdGraphSchema Interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override;
	virtual void GetGraphDisplayInformation(const UEdGraph& Graph, /*out*/ FGraphDisplayInfo& DisplayInfo) const override;
	virtual bool CanDuplicateGraph(UEdGraph* InSourceGraph) const override { return false; }



#pragma endregion



};
