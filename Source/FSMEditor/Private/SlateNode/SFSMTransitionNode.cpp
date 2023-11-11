// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateNode/SFSMTransitionNode.h"
#include "StateNode/FSMTransitionNode.h"
#include "StateNode/FSMStateNode_Base.h"
#include "ConnectionDrawingPolicy.h"

void SFSMTransitionNode::Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode)
{
	GraphNode = InNode;
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SFSMTransitionNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SImage)
						.Image(FEditorStyle::GetBrush("Graph.TransitionNode.ColorSpill"))
						.ColorAndOpacity(this, &SFSMTransitionNode::GetTransitionColor)
				]
				+ SOverlay::Slot()
				[
					SNew(SImage)
						.Image(this, &SFSMTransitionNode::GetTransitionIconImage)
				]
		];
}

void SFSMTransitionNode::PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& NodeToWidgetLookup) const
{
	UFSMTransitionNode* TransNode = CastChecked<UFSMTransitionNode>(GraphNode);

	// Find the geometry of the state nodes we're connecting
	FGeometry StartGeom;
	FGeometry EndGeom;

	int32 TransIndex = 0;
	int32 NumOfTrans = 1;

	UFSMStateNode_Base* PrevState = TransNode->GetPrevState();
	UFSMStateNode_Base* NextState = TransNode->GetNextState();
	if ((PrevState != NULL) && (NextState != NULL))
	{
		const TSharedRef<SNode>* pPrevNodeWidget = NodeToWidgetLookup.Find(PrevState);
		const TSharedRef<SNode>* pNextNodeWidget = NodeToWidgetLookup.Find(NextState);
		if ((pPrevNodeWidget != NULL) && (pNextNodeWidget != NULL))
		{
			const TSharedRef<SNode>& PrevNodeWidget = *pPrevNodeWidget;
			const TSharedRef<SNode>& NextNodeWidget = *pNextNodeWidget;

			StartGeom = FGeometry(FVector2D(PrevState->NodePosX, PrevState->NodePosY), FVector2D::ZeroVector, PrevNodeWidget->GetDesiredSize(), 1.0f);
			EndGeom = FGeometry(FVector2D(NextState->NodePosX, NextState->NodePosY), FVector2D::ZeroVector, NextNodeWidget->GetDesiredSize(), 1.0f);

			//TArray<UFSMTransitionNode*> Transitions;
			//PrevState->GetTransitionList(Transitions);

			//Transitions = Transitions.FilterByPredicate([NextState](const UAnimStateTransitionNode* InTransition) -> bool
			//	{
			//		return InTransition->GetNextState() == NextState;
			//	});

			//TransIndex = Transitions.IndexOfByKey(TransNode);
			//NumOfTrans = Transitions.Num();

			//PrevStateNodeWidgetPtr = PrevNodeWidget;
		}
	}

	//Position Node
	PositionBetweenTwoNodesWithOffset(StartGeom, EndGeom, TransIndex, NumOfTrans);
}

void SFSMTransitionNode::PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const
{
	// Get a reasonable seed point (halfway between the boxes)
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	// Find the (approximate) closest points between the two boxes
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

	// Position ourselves halfway along the connecting line between the nodes, elevated away perpendicular to the direction of the line
	const float Height = 30.0f;

	const FVector2D DesiredNodeSize = GetDesiredSize();

	FVector2D DeltaPos(EndAnchorPoint - StartAnchorPoint);

	if (DeltaPos.IsNearlyZero())
	{
		DeltaPos = FVector2D(10.0f, 0.0f);
	}

	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	const FVector2D NewCenter = StartAnchorPoint + (0.5f * DeltaPos) + (Height * Normal);

	FVector2D DeltaNormal = DeltaPos.GetSafeNormal();

	// Calculate node offset in the case of multiple transitions between the same two nodes
	// MultiNodeOffset: the offset where 0 is the centre of the transition, -1 is 1 <size of node>
	// towards the PrevStateNode and +1 is 1 <size of node> towards the NextStateNode.

	const float MutliNodeSpace = 0.2f; // Space between multiple transition nodes (in units of <size of node> )
	const float MultiNodeStep = (1.f + MutliNodeSpace); //Step between node centres (Size of node + size of node spacer)

	const float MultiNodeStart = -((MaxNodes - 1) * MultiNodeStep) / 2.f;
	const float MultiNodeOffset = MultiNodeStart + (NodeIndex * MultiNodeStep);

	// Now we need to adjust the new center by the node size, zoom factor and multi node offset
	const FVector2D NewCorner = NewCenter - (0.5f * DesiredNodeSize) + (DeltaNormal * MultiNodeOffset * DesiredNodeSize.Size());

	GraphNode->NodePosX = NewCorner.X;
	GraphNode->NodePosY = NewCorner.Y;
}

FSlateColor SFSMTransitionNode::GetTransitionColor() const
{
	return FLinearColor(0.9f, 0.9f, 0.9f, 1.0f);
	//UFSMTransitionNode* TransNode = CastChecked<UFSMTransitionNode>(GraphNode);
	//return StaticGetTransitionColor(TransNode, (IsHovered() || (PrevStateNodeWidgetPtr.IsValid() && PrevStateNodeWidgetPtr.Pin()->IsHovered())));
}

const FSlateBrush* SFSMTransitionNode::GetTransitionIconImage() const
{
	return FEditorStyle::GetBrush("Graph.TransitionNode.Icon_Inertialization");
	//UFSMTransitionNode* TransNode = CastChecked<UFSMTransitionNode>(GraphNode);
	//return (TransNode->LogicType == ETransitionLogicType::TLT_Inertialization)
	//	? FEditorStyle::GetBrush("Graph.TransitionNode.Icon_Inertialization")
	//	: FEditorStyle::GetBrush("Graph.TransitionNode.Icon");
}
