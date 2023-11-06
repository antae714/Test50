// Fill out your copyright notice in the Description page of Project Settings.


#include "StateNode/FSMStateNode_Base.h"
#include "KismetCompiledFunctionContext.h"

UFSMStateNode_Base::UFSMStateNode_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCanRenameNode = true;
}

void UFSMStateNode_Base::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Transition"), TEXT("In"));
	CreatePin(EGPD_Output, TEXT("Transition"), TEXT("Out"));
}

void UFSMStateNode_Base::Compile(FKismetFunctionContext& Context)
{
	Context.MessageLog.Note(
		*FString::Printf(TEXT("[%s] compile!"), *this->GetName())
	);
}
