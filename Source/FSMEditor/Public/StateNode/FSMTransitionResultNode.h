// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_FunctionResult.h"
#include "FSMTransitionResultNode.generated.h"

/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMTransitionResultNode : public UK2Node
{
	GENERATED_BODY()
public:
	virtual void AllocateDefaultPins() override;
	virtual bool CanUserDeleteNode() const { return false; }
	virtual bool CanDuplicateNode() const override { return false; }

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;
	void Setting();

	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;

public:
	UPROPERTY()
	FGuid transitionGuid;
	UPROPERTY()
	FName transitionName;
};
