// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMState.h"
#include "FSMStateNode.generated.h"

/**
 *
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMStateNode : public UFSMStateNode_Base
{
	GENERATED_BODY()
public:
#pragma region UEdGraphNode Interface
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void PostPasteNode() override;
	virtual void PostPlacedNewNode() override;
#pragma endregion

#pragma region UFSMStateNode_Base Interface
	virtual UEdGraph* GetBoundGraph() const override { return BoundGraph; }
	virtual FString GetNodeName() const override { return BoundGraph->GetName();  }
	virtual void Compile(struct FKismetFunctionContext& Context) const override;
#pragma endregion


	UPROPERTY()
	FFSMState State;
protected:
	UPROPERTY()
	TObjectPtr<class UEdGraph> BoundGraph;
};