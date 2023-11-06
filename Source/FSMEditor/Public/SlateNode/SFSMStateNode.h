// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateNode/SFSMStateNode_Base.h"

/**
 * 
 */
class FSMEDITOR_API SFSMStateNode : public SFSMStateNode_Base
{
	SLATE_BEGIN_ARGS(SFSMStateNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode);
	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

protected:
	FSlateColor GetBorderBackgroundColor() const;

	virtual const FSlateBrush* GetNameIcon() const;
};
