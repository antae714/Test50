// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "K2Node.h"
#include "FSMStateNode_Base.generated.h"

/**
 * 
 */
UCLASS()
class FINITESTATEMACHINEEDITOR_API UFSMStateNode_Base : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UFSMStateNode_Base(const FObjectInitializer& ObjectInitializer);


public:
#pragma region UEdGraphNode Interface
	virtual void AllocateDefaultPins() override;
	virtual UObject* GetJumpTargetForDoubleClick() const override;
	virtual bool CanJumpToDefinition() const override;
	virtual void JumpToDefinition() const override;
	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }
	virtual void OnRenameNode(const FString& NewName) override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PostPasteNode() override;
	virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;
	virtual void DestroyNode() override;
	virtual TArray<UEdGraph*> GetSubGraphs() const override;
#pragma endregion


	virtual void Compile(struct FKismetFunctionContext& Context) const;
	virtual UEdGraph* GetBoundGraph() const { return nullptr; }
	virtual FString GetNodeName() const;

};
