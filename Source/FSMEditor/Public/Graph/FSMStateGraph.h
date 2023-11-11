// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "FSMStateGraph.generated.h"


/**
 * 
 */
UCLASS()
class FSMEDITOR_API UFSMStateGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	class UFSMStateNode* owningNode;
};

//struct FTestGraphEditorSummoner : public FDocumentTabFactoryForObjects<UFSMGraph>
//{
//public:
//	//DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);
//	//FTestGraphEditorSummoner(TSharedPtr<class FTestEditor> InTestEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);
//	//virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;
//	//virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;
//protected:
//	//virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override;
//	//virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;
//
//};
