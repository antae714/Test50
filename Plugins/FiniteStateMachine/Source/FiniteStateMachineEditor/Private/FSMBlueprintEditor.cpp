// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMBlueprintEditor.h"
#include "FSMBlueprint.h"
#include "SMyBlueprint.h"

void FFSMBlueprintEditor::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UFSMBlueprint* InObject)
{
	InitBlueprintEditor(Mode, InitToolkitHost, { InObject }, false);
	
	//FKismetEditorUtilities::CreateDefaultEventGraphs(InObject);
	//OpenDocument(InObject->UbergraphPages.Last(), FDocumentTracker::OpenNewDocument);
	//UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(GetBlueprintObj(), "EventGraph", UEdGraph::StaticClass(), GetDefaultSchemaClass());
	//FBlueprintEditorUtils::AddUbergraphPage(GetBlueprintObj(), NewGraph);

	//SetDetailsCustomization(DetailsObjectFilter, DetailsRootCustomization);
	//SetSubobjectEditorUICustomization(SCSEditorUICustomization);
}
