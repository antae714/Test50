// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMStateEntryNode.h"

UFSMStateEntryNode::UFSMStateEntryNode(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	bCanRenameNode = false;
}

void UFSMStateEntryNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Entry"));
}
