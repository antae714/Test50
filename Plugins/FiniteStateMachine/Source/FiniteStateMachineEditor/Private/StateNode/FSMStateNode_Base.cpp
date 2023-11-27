// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMStateNode_Base.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/BlueprintEditorUtils.h"

class FSMeNodeNameValidator : public FStringSetNameValidator
{
public:
	FSMeNodeNameValidator(const UFSMStateNode_Base* InStateNode)
		: FStringSetNameValidator(FString())
	{
		TArray<UFSMStateNode_Base*> Nodes;
		UEdGraph* OwnerGraph = CastChecked<UEdGraph>(InStateNode->GetOuter());

		OwnerGraph->GetNodesOfClass<UFSMStateNode_Base>(Nodes);
		for (auto NodeIt = Nodes.CreateIterator(); NodeIt; ++NodeIt)
		{
			auto Node = *NodeIt;
			if (Node != InStateNode)
			{
				Names.Add(Node->GetNodeName());
			}
		}
	}
};


UFSMStateNode_Base::UFSMStateNode_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCanRenameNode = true;
}

void UFSMStateNode_Base::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Transition"), TEXT("In"));
	CreatePin(EGPD_Output, TEXT("Transition"), TEXT("Out"));
}

UObject* UFSMStateNode_Base::GetJumpTargetForDoubleClick() const
{
	UEdGraph* boundGraph = GetBoundGraph();
	if (boundGraph)
	{
		return boundGraph;
	}
	else
	{
		return nullptr;
	}
}

bool UFSMStateNode_Base::CanJumpToDefinition() const
{
	return !!GetJumpTargetForDoubleClick();
}

void UFSMStateNode_Base::JumpToDefinition() const
{
	if (UObject* HyperlinkTarget = GetJumpTargetForDoubleClick())
	{
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(HyperlinkTarget);
	}
}

void UFSMStateNode_Base::OnRenameNode(const FString& NewName)
{
	UEdGraph* boundGraph = GetBoundGraph();
	if (boundGraph)
	{
		FBlueprintEditorUtils::RenameGraph(boundGraph, NewName);
	}
	else 
	{
		Super::OnRenameNode(NewName);
	}
}

FText UFSMStateNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UEdGraph* boundGraph = GetBoundGraph();
	if (boundGraph)
	{
		return FText::FromString(boundGraph->GetName());
	}
	else 
	{
		return Super::GetNodeTitle(TitleType);
	}
}

void UFSMStateNode_Base::PostPasteNode()
{
	Super::PostPasteNode();

	for (UEdGraph* SubGraph : GetSubGraphs())
	{
		if (SubGraph)
		{
			// Add the new graph as a child of our parent graph
			UEdGraph* ParentGraph = GetGraph();

			if (ParentGraph->SubGraphs.Find(SubGraph) == INDEX_NONE)
			{
				ParentGraph->SubGraphs.Add(SubGraph);
			}

			//@TODO: CONDUIT: Merge conflict - May no longer be necessary due to other changes?
	//		FBlueprintEditorUtils::RenameGraphWithSuggestion(SubGraph, NameValidator, GetDesiredNewNodeName());
			//@ENDTODO

			// Restore transactional flag that is lost during copy/paste process
			SubGraph->SetFlags(RF_Transactional);

			UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ParentGraph);
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
		}
	}
}

TSharedPtr<class INameValidatorInterface> UFSMStateNode_Base::MakeNameValidator() const
{
	return MakeShareable(new FSMeNodeNameValidator(this));
}

void UFSMStateNode_Base::DestroyNode()
{
	UEdGraph* GraphToRemove = GetBoundGraph();

	Super::DestroyNode();

	if (GraphToRemove)
	{
		UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(this);
		FBlueprintEditorUtils::RemoveGraph(Blueprint, GraphToRemove, EGraphRemoveFlags::Recompile);
	}
}

TArray<UEdGraph*> UFSMStateNode_Base::GetSubGraphs() const
{
	UEdGraph* graph = GetBoundGraph();
	if (graph)
	{
		return TArray<UEdGraph*>({ graph });
	}
	else 
	{
		return Super::GetSubGraphs();
	}
}

void UFSMStateNode_Base::Compile(FKismetFunctionContext& Context) const
{


}

FString UFSMStateNode_Base::GetNodeName() const
{
	UEdGraph* boundGraph = GetBoundGraph();
	if (boundGraph)
	{
		return boundGraph->GetName();
	}
	else 
	{
		return TEXT("FSMStateNode");
	}
}
