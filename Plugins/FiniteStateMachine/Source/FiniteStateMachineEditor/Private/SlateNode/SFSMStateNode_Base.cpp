// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateNode/SFSMStateNode_Base.h"
#include "Widgets/Input/SComboBox.h"
#include "SGraphPin.h"

void SFSMStateNode_Base::Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode)
{
	GraphNode = InNode;
	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}
