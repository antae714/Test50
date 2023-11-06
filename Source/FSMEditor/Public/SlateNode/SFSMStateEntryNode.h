// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateNode/SFSMStateNode_Base.h"

/**
 * 
 */
class FSMEDITOR_API SFSMStateEntryNode : public SFSMStateNode_Base
{
	SLATE_BEGIN_ARGS(SFSMStateEntryNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode);

#pragma region SGraphNode
	virtual void UpdateGraphNode() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
#pragma endregion


protected:
	FSlateColor GetBorderBackgroundColor() const;

};
