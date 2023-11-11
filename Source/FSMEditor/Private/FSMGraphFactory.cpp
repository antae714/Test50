// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMGraphFactory.h"

#include "StateNode/FSMStateNode_Base.h"
#include "StateNode/FSMStateNode.h"
#include "StateNode/FSMStateEntryNode.h"
#include "StateNode/FSMTransitionNode.h"

#include "StateNode/FSMProcessNode.h"

#include "SlateNode/SFSMStateNode_Base.h"
#include "SlateNode/SFSMStateNode.h"
#include "SlateNode/SFSMStateEntryNode.h"
#include "SlateNode/SFSMTransitionNode.h"

#include "KismetPins/SGraphPinExec.h"
#include "FSMConnectionDrawingPolicy.h"
#include "Graph/FSMGraphSchema.h"

class STransparentGraphNode : public SGraphNode
{
	SLATE_BEGIN_ARGS(STransparentGraphNode) {}
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs, UEdGraphNode* InNode) 
	{
		GraphNode = InNode;
		SetVisibility(EVisibility::Collapsed);
	}
};

TSharedPtr<class SGraphNode> FFSMGraphNodeFactory::CreateNode(UEdGraphNode* InNode) const
{
	if (UFSMStateNode_Base* BaseStateNode = Cast<UFSMStateNode_Base>(InNode))
	{
		if (UFSMStateEntryNode* StateEntryNode = Cast<UFSMStateEntryNode>(InNode))
		{
			return SNew(SFSMStateEntryNode, BaseStateNode);
		}
		else if (UFSMStateNode* StateNode = Cast<UFSMStateNode>(InNode))
		{
			return SNew(SFSMStateNode, BaseStateNode);
		}
		else if (UFSMTransitionNode* TransitionNode = Cast<UFSMTransitionNode>(InNode))
		{
			return SNew(SFSMTransitionNode, BaseStateNode);
		}
	}
	else if (UFSMProcessNode* ProcesNode = Cast<UFSMProcessNode>(InNode))
	{
		return SNew(STransparentGraphNode, InNode);
	}

	return nullptr;
}

TSharedPtr<class SGraphPin> FFSMGraphPinFactory::CreatePin(UEdGraphPin* Pin) const
{
	if (Pin->GetSchema()->IsA<UFSMGraphSchema>() /*&& Pin->PinType.PinCategory == UEdGraphSchema_K2::PC_Exec*/)
	{
		return SNew(SGraphPinExec, Pin);
	}
	return nullptr;
}

FConnectionDrawingPolicy* FFSMGraphPinConnectionFactory::CreateConnectionPolicy(const UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	if (Schema->IsA(UFSMGraphSchema::StaticClass())) {
		return new FFSMConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	}
	return nullptr;
}
