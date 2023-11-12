// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMTransitionNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Graph/FSMTransitionGraph.h"
#include "Graph/FSMTransitionGraphSchema.h"


#include "KismetCompiledFunctionContext.h"
#include "FiniteStateMachine.h"

UFSMTransitionNode::UFSMTransitionNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCanRenameNode = false;
}

void UFSMTransitionNode::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Transition"), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Transition"), TEXT("Out"));
	Outputs->bHidden = true;
}

FText UFSMTransitionNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UFSMStateNode_Base* PrevState = GetPrevState();
	UFSMStateNode_Base* NextState = GetNextState();


	if ((PrevState != NULL) && (NextState != NULL))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("PrevState"), FText::FromString(PrevState->GetNodeName()));
		Args.Add(TEXT("NextState"), FText::FromString(NextState->GetNodeName()));

		return FText::Format(NSLOCTEXT("UFSMTransitionNode", "FSMPrevStateToNewState", "[{PrevState}]->[{NextState}]"), Args);
	}
	else
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("BoundGraph"), (BoundGraph != NULL) ? FText::FromString(BoundGraph->GetName()) : NSLOCTEXT("UFSMTransitionNode", "Null", "(null)"));
		// @TODO: FText::Format() is slow, and we could benefit from caching 
		//        this off like we do for a lot of other nodes (but we have to
		//        make sure to invalidate the cached string at the appropriate 
		//        times).
		return FText::Format(NSLOCTEXT("UFSMTransitionNode", "TransitioNState", "Trans {BoundGraph}}"), Args);
	}
}

void UFSMTransitionNode::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		// Commit suicide; transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UFSMTransitionNode::PostPlacedNewNode()
{
	// Create a new animation graph
	check(BoundGraph == NULL);
	BoundGraph = FBlueprintEditorUtils::CreateNewGraph(
		this, 
		NAME_None,
		UFSMTransitionGraph::StaticClass(),
		UFSMTransitionGraphSchema::StaticClass());
	check(BoundGraph);

	TSharedPtr<INameValidatorInterface> NameValidator = FNameValidatorFactory::MakeValidator(this);
	FBlueprintEditorUtils::RenameGraphWithSuggestion(BoundGraph, NameValidator, TEXT("Transition"));

	Cast<UFSMTransitionGraph>(BoundGraph)->owningNode = this;

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

UFSMStateNode_Base* UFSMTransitionNode::GetPrevState() const
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UFSMStateNode_Base>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UFSMStateNode_Base* UFSMTransitionNode::GetNextState() const
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UFSMStateNode_Base>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

void UFSMTransitionNode::CreateConnections(UFSMStateNode_Base* PreviousState, UFSMStateNode_Base* NextState)
{
	// Previous to this
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	PreviousState->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(PreviousState->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	NextState->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(NextState->GetInputPin());
}

void UFSMTransitionNode::PostPasteNode()
{
	Super::PostPasteNode();
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->LinkedTo.Num() == 0)
		{
			DestroyNode();
			break;
		}
	}
}

void UFSMTransitionNode::Compile(FKismetFunctionContext& Context) const
{
	UFiniteStateMachine* FSM_CDO = Context.NewClass->GetDefaultObject<UFiniteStateMachine>();
	int index = FSM_CDO->Transition.Emplace();
	FSM_CDO->Transition[index].Init(GetNodeName(), NodeGuid);
}
