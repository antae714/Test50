// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMGraphSchema.h"
#include "FSMGraph.h"
#include "Classes/EditorStyleSettings.h"

#include "StateNode/FSMStateEntryNode.h"
#include "StateNode/FSMStateNode.h"
#include "StateNode/FSMProcessNode.h"

#include "K2Node_FunctionEntry.h"

#include "Kismet2/BlueprintEditorUtils.h"


#define LOCTEXT_NAMESPACE "FSMSSchema"

TSharedPtr<FFSMGraphSchemaAction> AddNewStateNodeAction(FGraphContextMenuBuilder& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip, const int32 Grouping = 0)
{
	TSharedPtr<FFSMGraphSchemaAction> NewStateNode(new FFSMGraphSchemaAction(Category, MenuDesc, Tooltip, Grouping));
	ContextMenuBuilder.AddAction(NewStateNode);
	return NewStateNode;
}

UEdGraphNode* FFSMGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = NULL;

	// If there is a template, we actually use it
	if (NodeTemplate != NULL)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "K2_AddNode", "Add Node"));
		ParentGraph->Modify();
		if (FromPin)
		{
			FromPin->Modify();
		}

		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;
		NodeTemplate->SnapToGrid(GetDefault<UEditorStyleSettings>()->GridSnapSize);

		ResultNode = NodeTemplate;

		ResultNode->SetFlags(RF_Transactional);

		UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ParentGraph);
		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
	}

	return ResultNode;
}

void FFSMGraphSchemaAction::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);

	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
	Collector.AddReferencedObject(NodeTemplate);
}




void UFSMGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UFSMStateEntryNode* entryNode = nullptr;
	UFSMStateNode* statenode = nullptr;
	UFSMProcessNode* processNode = nullptr;
	Graph.Nodes.Empty();
	
	{
		FGraphNodeCreator<UFSMStateEntryNode> NodeCreator(Graph);
		entryNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(entryNode, FNodeMetadata::DefaultGraphNode);
	}

	{
		FGraphNodeCreator<UFSMProcessNode> NodeCreator(Graph);
		processNode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(processNode, FNodeMetadata::DefaultGraphNode);
	}

	{
		FGraphNodeCreator<UFSMStateNode> NodeCreator(Graph);
		statenode = NodeCreator.CreateNode();
		NodeCreator.Finalize();
		SetNodeMetaData(statenode, FNodeMetadata::DefaultGraphNode);
	}

	if (UFSMGraph* FSMGraph = CastChecked<UFSMGraph>(&Graph)) 
	{
		FSMGraph->EntryNode = entryNode;
		FSMGraph->ProcessNode = processNode;
	}
}

const FPinConnectionResponse UFSMGraphSchema::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
	if (!(PinA && PinB && PinA->GetOwningNode() && PinB->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
	}

	const bool bPinAIsEntry = PinA->GetOwningNode()->IsA(UFSMStateEntryNode::StaticClass());
	const bool bPinBIsEntry = PinB->GetOwningNode()->IsA(UFSMStateEntryNode::StaticClass());
	const bool bPinAIsStateNode = PinA->GetOwningNode()->IsA(UFSMStateNode_Base::StaticClass());
	const bool bPinBIsStateNode = PinB->GetOwningNode()->IsA(UFSMStateNode_Base::StaticClass());

	if (bPinAIsEntry || bPinBIsEntry)
	{
		if (bPinAIsEntry && bPinBIsStateNode)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
		}

		if (bPinBIsEntry && bPinAIsStateNode)
		{
			return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
		}

		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Entry must connect to a state node"));
	}


	if (PinA->GetOwningNode() == PinB->GetOwningNode()) return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
	


	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, TEXT("Create a transition"));
}

bool UFSMGraphSchema::TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	if (PinA->Direction == PinB->Direction)
	{
		if (UFSMStateNode_Base* BNode = Cast<UFSMStateNode_Base>(PinB->GetOwningNode()))
		{
			if (PinA->Direction == EGPD_Input)
			{
				PinB = BNode->GetOutputPin();
			}
			else {
				PinB = BNode->GetInputPin();
			}
		}
	}	
	const bool bModified = UEdGraphSchema::TryCreateConnection(PinA, PinB);
	if (bModified)
	{
		UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(PinA->GetOwningNode());
		FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
	}
	return bModified;
}

bool UFSMGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	if (PinA->Direction == EGPD_Input) 
	{
		PinA->Modify();
		PinB->Modify();
		PinA->MakeLinkTo(PinB);
	}
	else 
	{
		PinB->Modify();
		PinA->Modify();
		PinB->MakeLinkTo(PinA);
	}
	return true;
}

FLinearColor UFSMGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FLinearColor::White;
}

//bool UFSMGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
//{
//	const bool bModified = UEdGraphSchema::TryCreateConnection(A, B);
//
//	if (bModified)
//	{
//		UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(A->GetOwningNode());
//		FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
//	}
//
//	return bModified;
//}

//TSharedPtr<FEdGraphSchemaAction_NewStateNode> AddNewStateNodeAction(FGraphContextMenuBuilder& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip, const int32 Grouping = 0)
//{
//	TSharedPtr<FEdGraphSchemaAction_NewStateNode> NewStateNode(new FEdGraphSchemaAction_NewStateNode(Category, MenuDesc, Tooltip, Grouping));
//	ContextMenuBuilder.AddAction(NewStateNode);
//	return NewStateNode;
//}

void UFSMGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);
	{
		TSharedPtr<FFSMGraphSchemaAction> Action = AddNewStateNodeAction(ContextMenuBuilder, FText::GetEmpty(), LOCTEXT("AddState", "Add State..."), LOCTEXT("AddStateTooltip", "A new state"));
		Action->NodeTemplate = NewObject<UFSMStateNode>(ContextMenuBuilder.OwnerOfTemporaries);
	}
}

