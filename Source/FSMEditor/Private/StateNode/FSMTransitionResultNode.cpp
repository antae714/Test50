// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMTransitionResultNode.h"





void UFSMTransitionResultNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, TEXT("Result"));
}

FText UFSMTransitionResultNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return NSLOCTEXT("UFSMTransitionResultNode", "TransitionResultNodeName", "TransitionResult");
}

FLinearColor UFSMTransitionResultNode::GetNodeTitleColor() const
{
	return FLinearColor(1.0f, 0.0f, 0.0f, 0.0f);
}
