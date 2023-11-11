// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Node_CallFunction.h"
#include "FSMTransitionResultNode.generated.h"

/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMTransitionResultNode : public UK2Node_CallFunction
{
	GENERATED_BODY()
public:
	virtual void AllocateDefaultPins() override;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;

	virtual bool IsNodeRootSet() const override { return true; }

	UPROPERTY(EditAnywhere)
	FColor TransitionColor;
};
