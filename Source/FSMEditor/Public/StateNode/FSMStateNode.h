// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMStateNode.generated.h"

/**
 *
 */
UCLASS()
class FSMEDITOR_API UFSMStateNode : public UFSMStateNode_Base
{
	GENERATED_BODY()

public:
	//`FFSMState m_State;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
};