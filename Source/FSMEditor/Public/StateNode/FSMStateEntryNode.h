// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMStateNode_Base.h"
#include "FSMStateEntryNode.generated.h"

/**
 *
 */
UCLASS()
class FSMEDITOR_API UFSMStateEntryNode: public UFSMStateNode_Base
{
	GENERATED_BODY()
public:
	UFSMStateEntryNode(const FObjectInitializer& ObjectInitializer);

public:
#pragma region UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual UEdGraphPin* GetInputPin() const { return nullptr; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[0]; }
	virtual bool CanUserDeleteNode() const { return false; }
#pragma endregion
};