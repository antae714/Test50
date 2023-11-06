// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "FSMStateNode_Base.generated.h"

/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMStateNode_Base : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UFSMStateNode_Base(const FObjectInitializer& ObjectInitializer);

public:
#pragma region UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }
	//virtual void OnRenameNode(const FString& NewName) {  Rename(*NewName); }
#pragma endregion


	virtual void Compile(struct FKismetFunctionContext& Context);
};
