// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/FSMStateGraphSchema.h"
#include "StateNode/FSM_Event.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "StateNode/FSMStateNode.h"
#include "FSMState.h"
#include "Graph/FSMStateGraph.h"


void UFSMStateGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UFSMStateGraph* stateGraph = Cast<UFSMStateGraph>(&Graph);
	
	{
		FGraphNodeCreator<UFSM_Event> NodeCreator(Graph);
		UFSM_Event* eventNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(eventNode, FNodeMetadata::DefaultGraphNode);
		eventNode->SetDelegateName(FFSMState::StateEntryName);

		eventNode->NodePosY= 0;
		eventNode->MakeAutomaticallyPlacedGhostNode();
	}
	{
		FGraphNodeCreator<UFSM_Event> NodeCreator(Graph);
		UFSM_Event* eventNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(eventNode, FNodeMetadata::DefaultGraphNode);
		eventNode->SetDelegateName(FFSMState::StateUpdateName);

		eventNode->NodePosY = 125;
		eventNode->MakeAutomaticallyPlacedGhostNode();
	} 
	{
		FGraphNodeCreator<UFSM_Event> NodeCreator(Graph);
		UFSM_Event* eventNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(eventNode, FNodeMetadata::DefaultGraphNode);
		eventNode->SetDelegateName(FFSMState::StateExitName);

		eventNode->NodePosY = 250;
		eventNode->MakeAutomaticallyPlacedGhostNode();
	}
}

EGraphType UFSMStateGraphSchema::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_Ubergraph;
}

void UFSMStateGraphSchema::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const
{
	DisplayInfo.PlainName = FText::FromString(Graph.GetName());

	const UEdGraphNode* StateNode = Cast<const UEdGraphNode>(Graph.GetOuter());

	if (StateNode)
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("StateNodeTitle"), StateNode->GetNodeTitle(ENodeTitleType::FullTitle));
		DisplayInfo.PlainName = FText::Format(NSLOCTEXT("UFSMStateGraphSchema", "FSMStateGraphTitle", "[{StateNodeTitle}]"), Args);
	}

	DisplayInfo.DisplayName = DisplayInfo.PlainName;
}
