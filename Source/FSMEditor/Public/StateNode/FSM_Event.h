// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_Event.h"
#include "K2Node.h"
#include "FSM_Event.generated.h"

/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSM_Event : public UK2Node_Event
{
	GENERATED_BODY()
public:
#pragma region UEdGraphNode Interface
	virtual bool IsNodeRootSet() const override { return true; }
	virtual void AllocateDefaultPins() override;
	virtual bool CanUserDeleteNode() const { return false; }
	virtual bool CanDuplicateNode() const override { return false; }
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
	virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;

	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
#pragma endregion

	void SetDelegateName(FName _DelegateName);

public:
	UPROPERTY()
	FName DelegateName;
	UPROPERTY()
	FGuid StateGuid;
};
