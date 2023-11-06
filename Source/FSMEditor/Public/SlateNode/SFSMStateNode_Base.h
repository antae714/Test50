// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KismetNodes/SGraphNodeK2Base.h"
#include "StateNode/FSMStateNode_Base.h"

/**
 * 
 */
class FSMEDITOR_API SFSMStateNode_Base : public SGraphNode
{
	SLATE_BEGIN_ARGS(SFSMStateNode_Base) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFSMStateNode_Base* InNode);

};
