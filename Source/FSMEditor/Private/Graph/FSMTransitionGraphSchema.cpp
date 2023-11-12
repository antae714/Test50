// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/FSMTransitionGraphSchema.h"
#include "FSMTransition.h"

#include "Graph/FSMTransitionGraph.h"

#include "K2Node_FunctionEntry.h"
#include "K2Node_FunctionResult.h"

#include "StateNode/FSM_Event.h"
#include "StateNode/FSMTransitionNode.h"
#include "StateNode/FSMTransitionResultNode.h"

void UFSMTransitionGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UFSMTransitionGraph* TransitionGraph = Cast<UFSMTransitionGraph>(&Graph);
	UK2Node_FunctionEntry* FunctionEntryNode = nullptr;
	UFSMTransitionResultNode* TransitionResultNode = nullptr;

	{
		FGraphNodeCreator<UK2Node_FunctionEntry> NodeCreator(Graph);
		FunctionEntryNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(FunctionEntryNode, FNodeMetadata::DefaultGraphNode);
		/////////////////////////////////////////////////////////////////////////////////////////////////
		FunctionEntryNode->CustomGeneratedFunctionName = TransitionGraph->owningNode->GetFName();
	}
	{
		FGraphNodeCreator<UFSMTransitionResultNode> NodeCreator(Graph);
		TransitionResultNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(TransitionResultNode, FNodeMetadata::DefaultGraphNode);
		TransitionResultNode->Setting();
	}
	UEdGraphPin* FunctionEntryPin = FunctionEntryNode->FindPin(UEdGraphSchema_K2::PN_Then, EGPD_Output);
	UEdGraphPin* FunctionResultPin = TransitionResultNode->FindPin(UEdGraphSchema_K2::PN_Execute, EGPD_Input);

	FunctionEntryPin->MakeLinkTo(FunctionResultPin);
}

void UFSMTransitionGraphSchema::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const
{
	DisplayInfo.PlainName = FText::FromString(Graph.GetName());

	const UEdGraphNode* TransNode = Cast<const UEdGraphNode>(Graph.GetOuter());

	if (TransNode)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("TransNodeTitle"), TransNode->GetNodeTitle(ENodeTitleType::FullTitle));
		DisplayInfo.PlainName = FText::Format(NSLOCTEXT("UFSMTransitionGraphSchema", "TransitionGraphTitle", "{TransNodeTitle}"), Args);
	}

	DisplayInfo.DisplayName = DisplayInfo.PlainName;
}

EGraphType UFSMTransitionGraphSchema::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_Ubergraph;
}
