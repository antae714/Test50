// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMStateNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Graph/FSMStateGraph.h"
#include "Graph/FSMStateGraphSchema.h"

#include "KismetCompiledFunctionContext.h"
#include "FiniteStateMachine.h"

void UFSMStateNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	//@TODO: If the FromPin is a state, create a transition between us
	if (FromPin)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}


void UFSMStateNode::PostPasteNode()
{	
	// Find an interesting name, but try to keep the same if possible
	TSharedPtr<INameValidatorInterface> NameValidator = FNameValidatorFactory::MakeValidator(this);
	FBlueprintEditorUtils::RenameGraphWithSuggestion(BoundGraph, NameValidator, GetNodeName());

	for (UEdGraphNode* GraphNode : BoundGraph->Nodes)
	{
		GraphNode->CreateNewGuid();
		GraphNode->PostPasteNode();
		GraphNode->ReconstructNode();
	}

	Super::PostPasteNode();
}

void UFSMStateNode::PostPlacedNewNode()
{
	check(BoundGraph == NULL);
	BoundGraph = FBlueprintEditorUtils::CreateNewGraph(
		this,
		NAME_None,
		UFSMStateGraph::StaticClass(),
		UFSMStateGraphSchema::StaticClass());
	check(BoundGraph);

	// Find an interesting name
	TSharedPtr<INameValidatorInterface> NameValidator = FNameValidatorFactory::MakeValidator(this);
	FBlueprintEditorUtils::RenameGraphWithSuggestion(BoundGraph, NameValidator, TEXT("State"));

	Cast<UFSMStateGraph>(BoundGraph)->owningNode = this;

	// Initialize the anim graph
	const UEdGraphSchema* Schema = BoundGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*BoundGraph);

	// Add the new graph as a child of our parent graph
	UEdGraph* ParentGraph = GetGraph();

	if (ParentGraph->SubGraphs.Find(BoundGraph) == INDEX_NONE)
	{
		ParentGraph->SubGraphs.Add(BoundGraph);
	}
}

void UFSMStateNode::Compile(FKismetFunctionContext& Context) const
{
	UFiniteStateMachine* FSM_CDO = Context.NewClass->GetDefaultObject<UFiniteStateMachine>();
	int index = FSM_CDO->m_State.Emplace();
	FSM_CDO->m_State[index].Init({ GetNodeName() , NodeGuid });
}

