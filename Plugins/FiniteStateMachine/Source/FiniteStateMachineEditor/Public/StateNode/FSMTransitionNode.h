// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMTransitionNode.generated.h"

/**
 *
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMTransitionNode : public UFSMStateNode_Base
{
	GENERATED_BODY()

public:
	UFSMTransitionNode(const FObjectInitializer& ObjectInitializer);

public:
#pragma region UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PostPlacedNewNode() override;
	virtual void PostPasteNode() override;
#pragma endregion
#pragma region UFSMStateNode_Base Interface
	virtual UEdGraph* GetBoundGraph() const override { return BoundGraph; }
	virtual void Compile(struct FKismetFunctionContext& Context) const override;
#pragma endregion


	UFSMStateNode_Base* GetPrevState() const;
	UFSMStateNode_Base* GetNextState() const;
	void CreateConnections(UFSMStateNode_Base* PreviousState, UFSMStateNode_Base* NextState);
	//TEXT("Transition")

protected:
	UPROPERTY()
	TObjectPtr<class UEdGraph> BoundGraph;
};	
