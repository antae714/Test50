// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateNode/SFSMStateNode_Base.h"

/**
 * 
 */
class FSMEDITOR_API SFSMTransitionNode : public SFSMStateNode_Base
{
	SLATE_BEGIN_ARGS(SFSMTransitionNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode);
	
	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override {}
	virtual void UpdateGraphNode() override;	
	virtual bool RequiresSecondPassLayout() const override { return true; }
	virtual void PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup) const override;
	

	void PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const;

	FSlateColor GetTransitionColor() const;
	const FSlateBrush* GetTransitionIconImage() const;
};
