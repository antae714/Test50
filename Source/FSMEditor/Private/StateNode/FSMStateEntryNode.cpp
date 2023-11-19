// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMStateEntryNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "KismetCompiledFunctionContext.h"
#include "FiniteStateMachine.h"
#include "FSMBlueprintGeneratedClass.h"

UFSMStateEntryNode::UFSMStateEntryNode(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	bCanRenameNode = false;
}

void UFSMStateEntryNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, TEXT("Entry"));
}

void UFSMStateEntryNode::Compile(FKismetFunctionContext& Context) const
{
	UFSMBlueprintGeneratedClass* BPClass = Cast<UFSMBlueprintGeneratedClass>(Context.NewClass);
	BPClass->EnteryStateGUID = GetOutputPin()->LinkedTo[0]->GetOwningNode()->NodeGuid;
}
